# Web-server communicating with SQL-server

## Running the web-server

Expects the user have installed the rust-toolchain

    ```
    $ cargo run --release
    ```

Connect to http://YOUR_IP_ADDRESS:3000 and see all its glory

## Setup

1. Declare the database URL

    ```
    export DATABASE_URL="mariadb://root:password@localhost/todos"
    ```

2. Create the database.

    ```
    $ sqlx db create
    ```

3. Run sql migrations

    ```
    $ sqlx migrate run
    ```
