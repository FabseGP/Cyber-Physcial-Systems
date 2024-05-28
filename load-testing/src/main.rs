use reqwest::Client;
use serde::Deserialize;

#[derive(Deserialize, Debug)]
struct Car {
    car_id: i64,
    velocity: f64,
    clock: String,
    date_id: i64,
    traffic_light_id: i64,
}

#[derive(Deserialize, Debug)]
struct TrafficLight {
    traffic_light_id: i64,
    state: String,
    direction: String,
    location: String,
    queue_size: i64,
}

#[tokio::test]
async fn test_vehicle_insert_and_retrieve() {
    let client = Client::new();
    let num_iterations = 1000;

    // der løbes igennem 1000 iterationer
    for index in 0..num_iterations {
        let res = client
            // API'en tilgås for at indsætte en bil
            .post("http://localhost:3000/vehicles/insert")
            // alle parametre bortset fra bilens id holdes konstant
            .query(&[
                ("car_id", index),
                ("velocity", 60),
                ("date_id", 2),
                ("traffic_light_id", 2),
            ])
            .send()
            .await
            .expect("Failed to send request");

        // her tjekkes, om POST-requesten var en success
        assert!(res.status().is_success());

        let res = client
            // API'en tilgås for at returnere alle rækker i bil-tabellen
            .get("http://localhost:3000/vehicles/retrieve")
            .send()
            .await
            .expect("Failed to send request");

        // her tjekkes, om GET-requesten var en success
        assert!(res.status().is_success());

        // alle de returnerede rækker lagres i en vektor af Car-structen
        let cars: Vec<Car> = res.json().await.expect("Failed to parse response");
        assert!(!cars.is_empty());

        // for hvert bil tjekkes om der er en bil med det nuværende index 
        // og om date_id, car_type_id og traffic_light_id matcher det sendte
        let car = cars
            .iter()
            .find(|&c| c.car_id == index)
            .expect("Car not found");
        assert_eq!(car.date_id, 2);
        assert_eq!(car.traffic_light_id, 2);

        // der ventes 50ms for at simulere, hvor ofte en bil kan registreres
        std::thread::sleep(std::time::Duration::from_millis(50));
    }
}

#[tokio::test]
//#[ignore]
async fn test_traffic_light_insert_and_retrieve() {
    let client = Client::new();
    let num_iterations = 1000;

    for index in 0..num_iterations {
        let res = client
            .post("http://localhost:3000/trafficlights/insert")
            .query(&[
                ("traffic_light_id", "1"),
                ("state", "Green"),
                ("queue_size", &index.to_string()),
            ])
            .send()
            .await
            .expect("Failed to send request");
        assert!(res.status().is_success());

        let res = client
            .get("http://localhost:3000/trafficlights/retrieve")
            .send()
            .await
            .expect("Failed to send request");
        assert!(res.status().is_success());

        let traffic_lights: Vec<TrafficLight> = res.json().await.expect("Failed to parse response");
        assert!(!traffic_lights.is_empty());

        let traffic_light = traffic_lights
            .iter()
            .find(|&tl| tl.traffic_light_id == 1)
            .expect("Traffic light not found");
        assert_eq!(traffic_light.state, "Green");
        assert_eq!(traffic_light.queue_size, index);

        std::thread::sleep(std::time::Duration::from_millis(50));
    }
}

#[tokio::test]
#[ignore]
async fn test_traffic_light_insert_and_retrieve_old() {
    let client = Client::new();
    let num_iterations = 1000;

    for index in 0..num_iterations {
        let res = client
            .post("http://localhost:3000/trafficlights/insert")
            .query(&[
                ("traffic_light_id", "1"),
                ("state", "Green"),
                ("direction", "North"),
                ("location", "Willemoesgade 23, 5610 Assens"),
                ("queue_size", &index.to_string()),
            ])
            .send()
            .await
            .expect("Failed to send request");
        assert!(res.status().is_success());

        let res = client
            .get("http://localhost:3000/trafficlights/retrieve")
            .send()
            .await
            .expect("Failed to send request");
        assert!(res.status().is_success());

        let traffic_lights: Vec<TrafficLight> = res.json().await.expect("Failed to parse response");
        assert!(!traffic_lights.is_empty());

        let traffic_light = traffic_lights
            .iter()
            .find(|&tl| tl.traffic_light_id == 1)
            .expect("Traffic light not found");
        assert_eq!(traffic_light.state, "Green");
        assert_eq!(traffic_light.direction, "North");
        assert_eq!(traffic_light.location, "Willemoesgade 23, 5610 Assens");
        assert_eq!(traffic_light.queue_size, index);

        std::thread::sleep(std::time::Duration::from_millis(50));
    }
}
