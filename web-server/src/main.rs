// Crates/libraries imported, equal to #include in C/C++
use poem::{error::InternalServerError, listener::TcpListener, Result, Route, Server};
use poem_openapi::{param::Query, payload::Json, Object, OpenApi, OpenApiService, Tags};
use sqlx::types::{chrono, time};
use std::{env, sync::Arc};
use tokio_stream::StreamExt;

/// Define tags for api
#[derive(Tags)] // "Tags" is a trait within the poem_openapi-crate
                // It makes it possible to separate each api-methods under a tag in the UI
enum ApiTags {
    TrafficLights,
    Vehicles,
}

struct Api {
    // hvert request til API'en vil dele den samme forbindelse
    // typen omklammes af Arc for at tillade tasks at tilgå den samme pool
    db: Arc<sqlx::MySqlPool>,
}

impl Api {
    /// Establish a connection to a MySQL-/MariaDB-server given the credentials in the .env-file
    async fn etablish_sql_connection() -> Self {
        let db = {
            dotenvy::dotenv().unwrap();
            // læser login-informationerne til SQL-databasen i .env-filen
            let sql_user = env::var("MARIADB_USER").expect("MARIADB_USER must be set");
            let sql_password = env::var("MARIADB_PASSWORD").expect("MARIADB_PASSWORD must be set");
            let sql_database = env::var("MARIADB_DATABASE").expect("MARIADB_DATABASE must be set");

            Arc::new(
                sqlx::mysql::MySqlPoolOptions::new()
                    // maksimalt 5 child-forbindelser kan oprettes
                    .max_connections(5) 
                    .connect(&format!(
                        "mariadb://{sql_user}:{sql_password}@localhost/{sql_database}",
                    ))
                    .await
                    .expect("Couldn't connect to database"),
            )
        };
        // poolen lagres til API-structens db-felt
        Self { db } 
    }
}

/// A car is being represented here
// Assigning the struct the 'Object' trait from the poem_openapi-crate
// allows to fetch tables from the SQL-server and assign the individual attributes to variables
#[derive(Object)]
struct Car {
    car_id: i64,
    velocity: f64,
    clock: String,
    date_id: i64,
    traffic_light_id: i64,
}

/// A traffic light is being represented here
#[derive(Object)]
struct TrafficLight {
    traffic_light_id: i64,
    state: String,
    direction: String,
    location: String,
    queue_size: i64,
}

#[OpenApi]
impl Api {
    #[oai(path = "/vehicles/insert", method = "post", tag = "ApiTags::Vehicles")]
    // vehicle_insert-funktionen tilgås med en HTTP-POST request og forventer 5 parametre
    async fn vehicle_insert(
        &self,
        // hvert parameter er en String, der returneres fra API-querien
        car_id: Query<Option<String>>,
        velocity: Query<Option<String>>,
        date_id: Query<Option<String>>,
        traffic_light_id: Query<Option<String>>, 
    ) {
        // eksisterer der en række med samme car_id i tabellen, erstattes dens attributer af de sendte
        // hvis ikke, indsættes en ny række med attributerne
        sqlx::query!(
            "REPLACE INTO cars (car_id, velocity, clock, date_id, traffic_light_id) VALUES (?, ?, ?, ?, ?)",
            // as_deref (de = derive) bruges for at referere til parametrenes inderste værdi, 
            // dvs. String fremfor Query<Option<String>>
            car_id.as_deref(), velocity.as_deref(), chrono::Local::now(), date_id.as_deref(), traffic_light_id.as_deref()
        )
        .execute(&*self.db)
        .await
        .unwrap();
    }
    #[oai(path = "/vehicles/retrieve", method = "get", tag = "ApiTags::Vehicles")]
    // vehicle_retrieve-funktionen tilgås med en HTTP-GET request og returnerer alle rækker fra bil-tabellen
    async fn vehicle_retrieve(&self) -> Result<Json<Vec<Car>>> {
        let mut stream =
            // alle rækker fra bil-tabellen returneres 
            sqlx::query_as::<_, (i64, f64, time::Time, i64, i64)>("SELECT * FROM cars")
                .fetch(&*self.db);

        // da der ikke vides, hvor mange rækker tabellen har før runtime, laves en vektor for resultatet
        let mut results = Vec::new();

        // så længe der er en række, der ikke er tilgået endnu
        while let Some(res) = stream.next().await {
            // den nuværende række lagres i en array; hvis den er ufuldendt, returneres en server-error i stedet
            let query = res.map_err(InternalServerError)?;

            // hvert indeks i arrayet skubbes ind i vektoren som et objekt af Car-structen
            results.push(Car {
                car_id: query.0,
                velocity: query.1,
                clock: query.2.to_string(),
                date_id: query.3,
                traffic_light_id: query.4,
            });
        }
        
        // resultatet returneres i JSON-format
        Ok(Json(results))
    }

    #[oai(
        path = "/trafficlights/insert",
        method = "post",
        tag = "ApiTags::TrafficLights"
    )]
    /// Inserts information about a traffic light into the traffic_light-table within the SQL-server
    ///
    /// # Example
    ///
    /// ```
    /// traffic_light_insert("1", "Green", "North", "Nyborgsvej 3, 5530 Odense", "2")
    /// ```
    async fn traffic_light_insert(
        &self,
        traffic_light_id: Query<Option<String>>,
        state: Query<Option<String>>,
        queue_size: Query<Option<String>>,
    ) {
        sqlx::query!(/*
            "REPLACE INTO traffic_light (traffic_light_id, state, direction, location, queue_size) VALUES (?, ?, ?, ?, ?)",
            traffic_light_id.as_ref(), state.as_ref(), direction.as_ref(), location.as_ref(), queue_size.as_ref() */
            "UPDATE traffic_light SET state = ?, queue_size = ? WHERE traffic_light_id = ?",
            state.as_deref(), queue_size.as_deref(), traffic_light_id.as_deref()         
        )
        .execute(&*self.db)
        .await
        .unwrap();
    }
    #[oai(
        path = "/trafficlights/retrieve",
        method = "get",
        tag = "ApiTags::TrafficLights"
    )]
    /// Retrieves all rows from the traffic_light-table within the SQL-server
    ///
    /// # Example
    ///
    /// ```
    /// let traffic_lights = traffic_light_retrieve();
    /// match traffic_lights {
    ///    Ok(json) => println!("{:?}", json),
    ///    Err(err) => eprintln!("Error: {:?}", err),
    /// }
    /// ```
    async fn traffic_light_retrieve(&self) -> Result<Json<Vec<TrafficLight>>> {
        let mut stream =
            sqlx::query_as::<_, (i64, String, String, String, i64)>("SELECT * FROM traffic_light")
                .fetch(&*self.db);
        let mut results = Vec::new();
        while let Some(res) = stream.next().await {
            let query = res.map_err(InternalServerError)?;
            results.push(TrafficLight {
                traffic_light_id: query.0,
                state: query.1,
                direction: query.2,
                location: query.3,
                queue_size: query.4,
            });
        }
        Ok(Json(results))
    }
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    // laver en api ved http://localhost:3000 med navnet "TrafficAPI" og versionsnummeret "1.0.0"
    let api_service =
        OpenApiService::new(Api::etablish_sql_connection().await, "TrafficAPI", "1.0.0")
            .server("http://localhost:3000");
    let ui = api_service.swagger_ui();
    let spec = api_service.spec();

    // api'en knyttes til /, ui'en til /ui og speccet til /spec
    let route = Route::new()
        .nest("/", api_service)
        .nest("/ui", ui)
        .at("/spec", poem::endpoint::make_sync(move |_| spec.clone()));

    // http://localhost:3000 knyttes til http://0.0.0.0:3000, så det kan tilgås af alle på samme netværk
    Server::new(TcpListener::bind("0.0.0.0:3000"))
        .run(route)
        .await?;

    Ok(())
}
