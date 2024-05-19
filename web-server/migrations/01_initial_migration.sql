-- Create schema and tables

CREATE SCHEMA IF NOT EXISTS traffic_lights;

CREATE TABLE IF NOT EXISTS incident (
	date_id INTEGER NOT NULL,
	event CHAR(30) NOT NULL,
	calendar DATE NOT NULL,
	PRIMARY KEY (date_id)
);

CREATE TABLE IF NOT EXISTS car_type (
	car_type_id INTEGER NOT NULL,
	length DOUBLE NOT NULL,
	model CHAR(15) NOT NULL,
	PRIMARY KEY (car_type_id)
);

CREATE TABLE IF NOT EXISTS traffic_light (
	traffic_light_id INTEGER NOT NULL,
	state CHAR(15) NOT NULL,
	direction CHAR(15) NOT NULL,
	location CHAR(50) NOT NULL,
	queue_size INTEGER NOT NULL,
	PRIMARY KEY (traffic_light_id)
);

CREATE TABLE IF NOT EXISTS cars (
	car_id INTEGER NOT NULL,
	velocity DOUBLE(10, 5) NOT NULL,
	clock TIME(4) NOT NULL,
	date_id INTEGER NOT NULL,
	car_type_id INTEGER NOT NULL,
	traffic_light_id INTEGER NOT NULL,
	PRIMARY KEY (car_id),
	FOREIGN KEY (date_id) REFERENCES incident(date_id),
	FOREIGN KEY (car_type_id) REFERENCES car_type(car_type_id),
	FOREIGN KEY (traffic_light_id) REFERENCES traffic_light(traffic_light_id)
);

-- Insert dummy values into tables

INSERT INTO incident VALUES
	('1', "NA", '2024-03-22'),
	('2', "Bicycle race", '2024-03-23'),
	('3', "NA", '2024-03-24');

INSERT INTO car_type VALUES
	('1', '3.5', "Car"),
	('2', '10.0', "Truck"),
	('3', '5', "Car");
    
INSERT INTO traffic_light VALUES
	('0', "Green", "North", "Nyborgvej 23, 5530 Odense", '0'),
	('1', "Red", "South", "Damgårdsvej 40, 5530 Odense", '7'),
	('2', "Yellow", "West", "Marksvej 10, 5530 Odense", '7');

INSERT INTO cars VALUES
	('1', "50.0", '12:17:00.2020', '1', '2', '0'),
	('2', "20.0", '14:30:39.3002', '3', '1', '1'),
	('3', "10.0", '09:12:21.1021', '1', '1', '2');
