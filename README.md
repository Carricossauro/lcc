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

### Join

    client -> server
    "join#username password"

    server -> client
    "done" | "full_server" | "invalid_auth"

## Game

### Mouse

    server -> client
    "username color posx posy mass speed|username color posx posy mass speed|...|username color posx posy mass speed"

    client -> server
    "mouse#x y"

### Leave

    client -> server
    "leave"

    server -> client
    "ok"
