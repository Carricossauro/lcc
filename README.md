# Projeto PC

# Falta colocar os cristais

## Sintaxe

### Login

    client -> server
    "login#username password"

    server -> client
    "done" | "invalid_password" | "invalid_account"

### Logout

    client -> server
    "logout#username password"

    server -> client
    "done" | "invalid_password" | "invalid_account"

### Create Account

    client -> server
    "create_account#username password"

    server -> client
    "done" | "invalid_password" | "user_exists"

### Remove Account

    client -> server
    "remove_account#username password"

    server -> client
    "done" | "invalid_password" | "invalid_account"

### Leaderboard

    client -> server
    "leaderboard#"

    server -> client
    "username score|username score|...|username score"

### Online

    client -> server
    "online#"

    server -> client
    "username username ... username"

## Game

### mvklsdlfm

    server -> client
    "username color posx posy mass|username color posx posy mass|...|username color posx posy mass"

    client -> server
    "mouse#username x y"
