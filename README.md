# Bank application (Qt6 framework)
This is a final project for Computer Programming course at the [Silesian University of Technology](https://www.polsl.pl/en/) for the 2nd semester 2024/2025 of Informatics.

## Description
The bank project is a Qt6 framework-based application which simulates basic bank functionalities in an isolated environment provided by the sqlite database.
The functionalities are:
- Creating new user
- Adding accounts to the user
- Depositing/Withdrawing
- Transfers
- Interest (Savings account)

## Important note
In order to do anything useful within the application you must load the database file from the menu bar
and also insert **admin account**.
Example admin insertion command:
```sql
INSERT INTO users (username, password) VALUES ('admin', 'password');
```

## Prerequisites
- The project was developed in [**Qt Creator**](https://doc.qt.io/qtcreator/) IDE, therefore it is recommended to use it for compilation.
- [**vcpkg**](https://vcpkg.io) package manager for installing fmt and sqlite_orm libraries.
- sqlite database with following database structure:
```sql
CREATE TABLE users (
    id INTEGER PRIMARY KEY,
    username VARCHAR(64),
    password VARCHAR(64)
);

CREATE TABLE personal_accounts (
    id INTEGER PRIMARY KEY,
    user_id INTEGER UNIQUE,
    balance INTEGER,
    FOREIGN KEY (user_id) REFERENCES users(id)
);

CREATE TABLE savings_accounts (
    id INTEGER PRIMARY KEY,
    user_id INTEGER NOT NULL UNIQUE,
    balance INTEGER NOT NULL,
    last_login INTEGER DEFAULT(-1),
    FOREIGN KEY (user_id) REFERENCES users(id)
);
```

## Troubleshooting
In case where Qt Creator doesn't detect the installed locally packages, try to run `vcpkg integrate install` in order to make packages system-wide.
After that clone repository again and open it in the IDE.

---
#### &copy; 2025 Xawier Słupik - Licensed under MIT License
