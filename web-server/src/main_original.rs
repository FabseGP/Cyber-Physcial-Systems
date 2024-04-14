use poem::{error::InternalServerError, listener::TcpListener, Result, Route, Server};
use poem_openapi::{param::Query, payload::Json, Object, OpenApi, OpenApiService, Tags};
use sqlx::types::{chrono, time};
use std::{env, sync::Arc};
use tokio_stream::StreamExt;

#[derive(Tags)]
enum ApiTags {
    TrafficLights,
    Vehicles,
}

pub struct Data {
    pub db: sqlx::MySqlPool,
}

impl Data {
    pub async fn new() -> Self {
        let db = establish_connection().await;
        Self { db }
    }
}

async fn establish_connection() -> sqlx::MySqlPool {
    let sql_user = env::var("MARIADB_USER").expect("MARIADB_USER must be set");
    let sql_password = env::var("MARIADB_PASSWORD").expect("MARIADB_PASSWORD must be set");
    let sql_database = env::var("MARIADB_DATABASE").expect("MARIADB_DATABASE must be set");

    sqlx::mysql::MySqlPoolOptions::new()
        .max_connections(5)
        .connect(&format!(
            "mariadb://{username}:{password}@localhost/{database}",
            username = sql_user,
            password = sql_password,
            database = sql_database
        ))
        .await
        .expect("Couldn't connect to database")
}

struct Api {
    data: Arc<Data>,
}

impl Api {
    fn new(data: Arc<Data>) -> Self {
        Self { data }
    }
}

#[derive(Object)]
struct Cars {
    car_id: i64,
    velocity: i64,
    clock: String,
    date_id: i64,
    car_type_id: i64,
    traffic_light_id: i64,
}

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
    async fn vehicle_insert(
        &self,
        car_id: Query<Option<String>>,
        velocity: Query<Option<String>>,
        date_id: Query<Option<String>>,
        car_type_id: Query<Option<String>>,
        traffic_light_id: Query<Option<String>>,
    ) {
        /*
        if car_id.is_some()
            && velocity.is_some()
            && date_id.is_some()
            && car_type_id.is_some()
            && traffic_light_id.is_some()
        {*/
        sqlx::query!(
            "REPLACE INTO cars (car_id, velocity, clock, date_id, car_type_id, traffic_light_id) VALUES (?, ?, ?, ?, ?, ?)",
            car_id.as_ref(), velocity.as_ref(), chrono::Local::now(), date_id.as_ref(), car_type_id.as_ref(), traffic_light_id.as_ref()
        )
        .execute(&self.data.db)
        .await
        .unwrap();
        //}
    }
    #[oai(path = "/vehicles/retrieve", method = "get", tag = "ApiTags::Vehicles")]
    async fn vehicle_retrieve(&self) -> Result<Json<Vec<Cars>>> {
        let mut stream =
            sqlx::query_as::<_, (i64, i64, time::Time, i64, i64, i64)>("SELECT * FROM cars")
                .fetch(&self.data.db);
        let mut results = Vec::new();
        while let Some(res) = stream.next().await {
            let query = res.map_err(InternalServerError)?;
            results.push(Cars {
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
        .execute(&self.data.db)
        .await
        .unwrap();
    }
    #[oai(
        path = "/trafficlights/retrieve",
        method = "get",
        tag = "ApiTags::TrafficLights"
    )]
    async fn traffic_light_retrieve(&self) -> Result<Json<Vec<TrafficLight>>> {
        let mut stream =
            sqlx::query_as::<_, (i64, String, String, String, i64)>("SELECT * FROM traffic_light")
                .fetch(&self.data.db);
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
    dotenvy::dotenv().unwrap();

    let data = Arc::new(Data::new().await);
    let api_service =
        OpenApiService::new(Api::new(data), "Fabseapi", "1.0.0").server("http://localhost:3000");
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
