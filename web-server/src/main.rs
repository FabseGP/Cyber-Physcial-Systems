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

/// An api is represented here
struct Api {
    /// Each api-request must have access to the database-connection
    // Data shared within the api must be of Arc-type to allow concurrent threads access
    db: Arc<sqlx::MySqlPool>,
}

impl Api {
    /// Establish a connection to a MySQL-/MariaDB-server given the credentials in the .env-file
    async fn etablish_sql_connection() -> Self {
        let db = {
            dotenvy::dotenv().unwrap();
            let sql_user = env::var("MARIADB_USER").expect("MARIADB_USER must be set");
            let sql_password = env::var("MARIADB_PASSWORD").expect("MARIADB_PASSWORD must be set");
            let sql_database = env::var("MARIADB_DATABASE").expect("MARIADB_DATABASE must be set");

            Arc::new(
                sqlx::mysql::MySqlPoolOptions::new()
                    .max_connections(5) // In this case a connection should only be established once, so partly unneccesary
                    .connect(&format!(
                        "mariadb://{sql_user}:{sql_password}@localhost/{sql_database}",
                    ))
                    .await
                    .expect("Couldn't connect to database"),
            )
        };
        Self { db } // Assigns the content of the 'local' db within this function to the 'shared' db within the Api-struct
    }
}

/// A car is being represented here
// Assigning the struct the 'Object' trait from the poem_openapi-crate
// allows to fetch tables from the SQL-server and assign the individual attributes to variables
#[derive(Object)]
struct Car {
    car_id: i64,
    velocity: i64,
    clock: String,
    date_id: i64,
    car_type_id: i64,
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
    /// Inserts information about a passing car into the cars-table within the SQL-server
    ///
    /// # Example
    ///
    /// ```
    /// vechicle_insert("1", "30", "2", "3", "5")
    /// ```
    async fn vehicle_insert(
        &self,
        car_id: Query<Option<String>>,
        velocity: Query<Option<String>>,
        date_id: Query<Option<String>>,
        car_type_id: Query<Option<String>>,
        traffic_light_id: Query<Option<String>>,
    ) {
        sqlx::query!(
            "REPLACE INTO cars (car_id, velocity, clock, date_id, car_type_id, traffic_light_id) VALUES (?, ?, ?, ?, ?, ?)",
            car_id.as_ref(), velocity.as_ref(), chrono::Local::now(), date_id.as_ref(), car_type_id.as_ref(), traffic_light_id.as_ref()
        )
        .execute(&*self.db)
        .await
        .unwrap();
    }
    #[oai(path = "/vehicles/retrieve", method = "get", tag = "ApiTags::Vehicles")]
    /// Retrieves all rows from the cars-table within the SQL-server
    ///
    /// # Example
    ///
    /// ```
    /// let cars = vechicle_retrieve();
    /// match cars {
    ///    Ok(json) => println!("{:?}", json),
    ///    Err(err) => eprintln!("Error: {:?}", err),
    /// }
    /// ```
    async fn vehicle_retrieve(&self) -> Result<Json<Vec<Car>>> {
        let mut stream =
            sqlx::query_as::<_, (i64, i64, time::Time, i64, i64, i64)>("SELECT * FROM cars")
                .fetch(&*self.db);
        let mut results = Vec::new();
        while let Some(res) = stream.next().await {
            let query = res.map_err(InternalServerError)?;
            results.push(Car {
                car_id: query.0,
                velocity: query.1,
                clock: query.2.to_string(),
                date_id: query.3,
                car_type_id: query.4,
                traffic_light_id: query.5,
            });
        }
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
        direction: Query<Option<String>>,
        location: Query<Option<String>>,
        queue_size: Query<Option<String>>,
    ) {
        sqlx::query!(
            "REPLACE INTO traffic_light (traffic_light_id, state, direction, location, queue_size) VALUES (?, ?, ?, ?, ?)",
            traffic_light_id.as_ref(), state.as_ref(), direction.as_ref(), location.as_ref(), queue_size.as_ref()
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
/// Initializes an async api at http://localhost:3000
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    let api_service =
        OpenApiService::new(Api::etablish_sql_connection().await, "TrafficAPI", "1.0.0")
            .server("http://localhost:3000");
    let ui = api_service.swagger_ui();
    let spec = api_service.spec();
    let route = Route::new()
        .nest("/", api_service)
        .nest("/ui", ui)
        .at("/spec", poem::endpoint::make_sync(move |_| spec.clone()));

    Server::new(TcpListener::bind("0.0.0.0:3000"))
        .run(route)
        .await?;

    Ok(())
}
