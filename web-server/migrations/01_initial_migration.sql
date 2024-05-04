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
	velocity INTEGER NOT NULL,
	clock TIME NOT NULL,
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
	('0', "Green", "North", "Nyborgvej, 5530 Odense", '0'),
	('1', "Red", "South", "Damgårdsvej, 5530 Odense", '7'),
	('2', "Yellow", "West", "Marksvej, 5530 Odense", '7'),
	('3', "Yellow", "West", "Marksvej, 5530 Odense", '7');

INSERT INTO cars VALUES
	('1', "50", '12:17:00', '1', '2', '3'),
	('2', "20", '14:30:39', '3', '1', '1'),
	('3', "10", '09:12:21', '1', '1', '2');
