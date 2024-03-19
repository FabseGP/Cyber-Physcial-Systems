CREATE SCHEMA IF NOT EXISTS light_crossings;

CREATE TABLE IF NOT EXISTS incident (
    date_id INTEGER NOT NULL,
    velocity INTEGER NOT NULL,
    event char(25) NOT NULL,
    PRIMARY KEY (date_id)
);

CREATE TABLE IF NOT EXISTS car_type (
    car_type_id INTEGER NOT NULL,
    length DOUBLE NOT NULL,
    brand char(25) NOT NULL,
    PRIMARY KEY (car_type_id)
);

CREATE TABLE IF NOT EXISTS traffic_light (
    traffic_light_id INTEGER NOT NULL,
    state INTEGER NOT NULL,
    track INTEGER NOT NULL,
    queue_size INTEGER NOT NULL,
    PRIMARY KEY (traffic_light_id)
);

CREATE TABLE IF NOT EXISTS cars (
    car_id INTEGER NOT NULL,
    velocity INTEGER NOT NULL,
    clock TIME NOT NULL,
    PRIMARY KEY (car_id),
    FOREIGN KEY (date_id) INTEGER NOT NULL,
    FOREIGN KEY (car_type_id) INTEGER NOT NULL,
    FOREIGN KEY (traffic_light_id) INTEGER NOT NULL
);
