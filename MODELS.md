# Table of Contents

* [General task diagram V1](#general-task-diagram-v1)
* [General task diagram V2](#general-task-diagram-v2)
* [Implementing hardware functions](#implementing-hardware-functions)
* [Implementing software functions](#implementing-software-functions)
* [SQL schema](#sql-schema) 

# General task diagram V1

```mermaid
flowchart TD
    A[Sensor] --> B[[Sensor-buffer]] --> C[Data-model]
    C --> D[Traffic-data] --> E((Datatransmission)) --> F[SQL-server]
    C --> G[Queue-data] --> H((Traffic-light algorithm)) --> I[Traffic-light mode]

```

# General task diagram V2

```mermaid
flowchart LR
    A{PCNT0-interrupt} --> C[[Sensor1 buffer]]
    B{PCNT1-interrupt} --> D[[Sensor2 buffer]]

    C --> I((Velocity and position)) 
    D --> I

    I --> E[Car data]
    I --> F[Queue size]

    E --> H((Data-parsing))
    F --> H

    H --> G[[HTTP-buffer]] --> K((Wifi-transfer)) --> P[[SQL-data]] --> Q((Populating SQL-database))
 
    E --> J((Traffic light algorithm))
    F --> J

    J --> L[Traffic light state] --> N((Traffic light switching)) 
    J --> O[Traffic light timeout] --> M{Timer-interrupt} --> N

```

# Implementing hardware functions

```mermaid
journey
	title Hardware functions
	section System timer (systick)
		Research into registers: Placeholder
		Testing modes (time-delay vs periodic): Placeholder
		Write function with inputs to set timer & mode: Placeholder
	section Timer interrupts
		Research into difference between timer group 0 & 1: Placeholder
		Testing modes (counter vs external): Placeholder
		Write function with inputs to set prescaler & mode: Placeholder
		Decide whether PCNT is a must have for noticing frequency changes: Placeholder
	section UART
		Research into difference between UART0 & UART1: Placeholder
		Test blocking TX & RX: Placeholder
		Test interrupt-based TX & RX: Placeholder
		Write functions to send strings by individual characters: Placeholder
	section WiFi-connection (using ESP-IDF-libraries)
		Research into WiFi-modes: Placeholder
		Test the example projects in the ESP-IDF-repo: Placeholder
		Testing connection to web-server (with dummy transactions): Placeholder
```

# Implementing software functions

```mermaid
journey
	title Software functions
	section Traffic-lights 
		Decide on duration for each mode (red, redyellow, yellow & green): Placeholder
		Decide on whether to control each traffic-light by state or by struct: Placeholder
		Implement traffic-light modes with systick: Placeholder
	section Sensors 
		Outline needed calculations: Placeholder
		Implement reading of signal-frequency (1 period either by using rise-/fall-time or PCNT): Placeholder
		Create a data model for the data types, i.e. array/buffer for car-queue: Placeholder
	section Algorithm
		Decide on traffic-light switching (weights given vehicle type, queue-size, duration on go/stop etc.): Placeholder
		Consider method to search through data (for-loop through array vs binary search vs hashmap): Placeholder
		Implement functions that either returns set state (i.e. go or stop) or link it to a buffer: Placeholder
	section SQL-connection (either MariaDB or SQLite3)
		Find general-purpose SQL-library with ESP32-support: Placeholder
		Connect to SQL-server and insert dummy data: Placeholder
		Write function with inputs to send either numbers or text: Placeholder
	section Scheduling
		Discuss (dis)advantages of different scheduler models: Placeholder
		Implement all functions as tasks (i.e. initialization, traffic-light mode, data reading/writing, sql-server etc.): Placeholder
		Either implement our own scheduler or look into FreeRTOS: Placeholder
```

# SQL schema

```mermaid
erDiagram
    VEHICLE {
        int car_id PK
        int velocity
	time hours
	int date_id FK
	int car-model_id FK
	int traffic-light_id FK
    }
    CAR-MODEL ||--o{ VEHICLE : is
    CAR-MODEL {
        int car-model_id PK
        double length
        char(25) model "I.e. car, truck, bus etc."
    }
    DATE ||--o{ VEHICLE : allows
    DATE {
        int date_id PK
        date date 
        char(25) event "Occasions that might cause traffic jams"
    }
    TRAFFIC-LIGHT ||--o{ VEHICLE : allows
    TRAFFIC-LIGHT {
        int traffic-light_id PK
        int char(25) "Either red, redyellow, yellow or green"
        char(25) direction "Either north, south, east or west"
        char(25) location
        queue_size int
    }
```
