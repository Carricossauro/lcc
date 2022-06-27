url: profile/

tipo: GET

função: obter a informação do user que esta autenticado

requisitos: autenticação

resposta:


{
    "id": 9,
    "username": "yyy",
    "name": "yyy",
    "birthday": null,
    "email": "yyy@gmail.com",
    "type": "A"
}
 
correcto - Status 200

errado - Status 401


---------------------------------------------------------


url: profile/password/

tipo: POST

função: aletar password do user autenticado

requisitos: autenticação

pedido:

{
    "current":"zoisper",
    "new":"zoisper"
}

resposta:

correcto - Status 200

errado - Status 403

nota: em caso de nao ser enviada uma nova password, a password fica por padrao a ser o nome de utilizador


---------------------------------------------------------

url: users/

tipo POST

função: inserir um user

pedido:

{
    "username": "username",
    "name": "name",
    "password": "password",
    "email": "email",
    "type": "A"
}


resposta:


correcto - Status 201

errado - Status 400

nota: o 'type' pode ser 'A' ou 'P' e o 'birthday' é opcional


---------------------------------------------------------

url: users/<str:username>


tipo: GET

função: obter a informação do user que esta autenticado e com 'usernanme' = <str:username>

requisitos: autenticação

resposta:



{
    "id": 9,
    "username": "yyy",
    "name": "yyy",
    "birthday": null,
    "email": "yyy@gmail.com",
    "type": "A"
}
 
correcto - Status 200

errado - Status 404

---------------------------------------------------------


url: questions/

tipo: GET

função: obter todas as questões

requisitos: autenticação

resposta:

[
    {
        "id": 1,
        "author": "zoisper",
        "title": "Teste",
        "type": "SA",
        "score": 10,
        "dificulty": "E",
        "minage": 1,
        "options": [
            {
                "id": 55,
                "answer": "ola",
                "question": 1,
                "correct": true
            }
        ],
        "contents": [
            {
                "id": 116,
                "question": 1,
                "order": 1,
                "type": "A",
                "text": "",
                "media": null
            }
        ]
    },
    {
        "id": 4,
        "author": "tiago",
        "title": "This field is required.",
        "type": "TF",
        "score": 1,
        "dificulty": "H",
        "minage": 4,
        "options": [],
        "contents": []
    }
]


correcto - 200

errado - 401

nota: Se for Player a fazer pedido a informaçao 'correct' das options é removida

---------------------------------------------------------


url: questions/<int:id>

tipo: GET

função: obter a questão com 'id' = <int:id>


resposta:


{
    "id": 22,
    "author": "xxx",
    "title": "Teste",
    "type": "SA",
    "score": 10,
    "dificulty": "E",
    "minage": 1,
    "options": [
        {
            "id": 31,
            "answer": "ola",
            "question": 22,
            "correct": true
        }
    ],
    "contents": [
        {
            "id": 75,
            "question": 22,
            "order": 1,
            "type": "A",
            "text": "\"\"",
            "media": null
        }
    ]
}

correcto - 200

errado - 404

nota: Se for Player a fazer pedido a informaçao 'correct' das options é removida

---------------------------------------------------------


url: questions/user/

tipo: GET

função: obter todas as questoes do utilizador autenticado

requisito: autenticação

resposta:

[
    {
        "id": 1,
        "author": "zoisper",
        "title": "Teste",
        "type": "SA",
        "score": 10,
        "dificulty": "E",
        "minage": 1,
        "options": [
            {
                "id": 55,
                "answer": "ola",
                "question": 1,
                "correct": true
            }
        ],
        "contents": [
            {
                "id": 116,
                "question": 1,
                "order": 1,
                "type": "A",
                "text": "",
                "media": null
            }
        ]
    },
    {
        "id": 19,
        "author": "zoisper",
        "title": "Teste",
        "type": "SA",
        "score": 1,
        "dificulty": "E",
        "minage": 1,
        "options": [
            {
                "id": 2,
                "answer": "[a-z][0-9][a-z][0-9]+",
                "question": 19,
                "correct": true
            }
        ],
        "contents": []
    }
]

correto - 200

errado - 401

---------------------------------------------------------

url: questions/update/<int:id>

tipo: PUT

função: aleterar uma questão

requisitos: Autenticação, Ser Proprietario

pedido:

{
        "title": "Teste",
        "type": "SA",
        "score": 10,
        "dificulty": "E",
        "minage": 1,
        "options": [
            {
                "id": 63,
                "answer": "ola",
                "correct": true
            }
        ],
        "contents": [
            {
                "id":127,
                "order": 1,
                "type": "A",
                "text": ""
            }
        ]
    }
reposta:


{
    "id": 22,
    "author": 8,
    "title": "Teste",
    "type": "SA",
    "score": 10,
    "dificulty": "E",
    "minage": 1,
    "options": [
        {
            "id": 63,
            "answer": "ola",
            "question": 22,
            "correct": true
        }
    ],
    "contents": [
        {
            "id": 127,
            "question": 22,
            "order": 1,
            "type": "A",
            "text": "",
            "media": null
        }
    ]
}

correto - 201

errado - 403 ou 404

nota: os campos que nao forem enviado serão mantidos. Nas 'options' e 'contents', se o 'id' nao fore enviado os anteriores são todos apagados e criados novos 

---------------------------------------------------------


url: questions/insert/

tipo: POST

função: inserir uma questão

requisitos: Autenticação, Ser Autor

pedido:

{
    "title": "This field is required.",
    "type": "This field is required.",
    "score": "This field is required.",
    "dificulty": "This field is required.",
    "minage": "This field is required.",
    "options": "This field is required.",
    "contents": "This field is required."
}


exemplo:

{
        "title": "Teste",
        "type": "SA",
        "score": 10,
        "dificulty": "E",
        "minage": 1,
        "options": [
            {
                "answer": "ola",
                "correct": true
            }
        ],
        "contents": [
            {
                "order": 1,
                "type": "A",
                "text": ""
                "media":"optional"
            }
        ]
}


resposta:

correto - 201

errado - 401 ou 403

nota: 'options' e 'contents' são uma listas e o 'media' é opcional

---------------------------------------------------------

url: history/

tipo: POST

função: responder a uma pergunta

requisitos: Autenticação, Ser Player

pedido:

{
    "question": "1",
    "answer": "ola"
}

resposta:

{
    "id": 76,
    "player": 9,
    "question": 1,
    "date": "2022-06-27T01:09:23Z",
    "correct": true,
    "answer": "ola"
}


correto - 201

errado - 404 ou 401


---------------------------------------------------------


url: history/user/

tipo: GET

função: obter o historico de respostas do utilizador autenticado

requisitos: Autenticação

resposta:

[
    {
        "id": 64,
        "player": "yyy",
        "question": 22,
        "date": "2022-06-26T22:01:41Z",
        "correct": true,
        "answer": "ola"
    },
    {
        "id": 65,
        "player": "yyy",
        "question": 22,
        "date": "2022-06-26T22:02:10Z",
        "correct": true,
        "answer": "ola"
    }
]

correto - 200

errado - 401

---------------------------------------------------------

url: history/question/<int:id>

tipo: GET

função: obter o historico de respostas à questão com 'id' = <int:id>

requisitos: Autenticação, Ser Proprietário

resposta:

[
    {
        "id": 67,
        "player": "yyy",
        "question": 1,
        "date": "2022-06-26T22:06:16Z",
        "correct": true,
        "answer": "ola"
    },
    {
        "id": 68,
        "player": "yyy",
        "question": 1,
        "date": "2022-06-27T00:04:25Z",
        "correct": true,
        "answer": "ola"
    }
]

correto - 200

errado - 404 ou 410

---------------------------------------------------------

url: login/'

tipo: POST

função: Autenticar um utilizador

pedido:

{
    "username": "yyy",
    "password":"yyy"
}

resposta:

{
    "refresh": "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ0b2tlbl90eXBlIjoicmVmcmVzaCIsImV4cCI6MTY1NjM3ODUzMiwiaWF0IjoxNjU2MjkyMTMyLCJqdGkiOiIyMjFjZjAzYWUxODE0Nzc5ODI3NjNmOWMxOGYwYjY1MyIsInVzZXJfaWQiOjl9.8Qlwm7xgbjZFEH0ndK7CiNS1P-D4FCoRnPb4jLf7-Io",
    
    "access": "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ0b2tlbl90eXBlIjoiYWNjZXNzIiwiZXhwIjoxNjU2Mjk1NzMyLCJpYXQiOjE2NTYyOTIxMzIsImp0aSI6IjdlMTM3OTE5OWM1OTQ3NWViODFmMGQ2Y2MyMWU1OTFkIiwidXNlcl9pZCI6OX0.TDjrl61WosT_hMp1UMCOCI-iG3DZnU93QKuu3aIAVho"
}


correto - 200

errado - 401

---------------------------------------------------------


url: login/refresh/'

tipo: POST

função: Atualizar o token quando este expira

pedido:

{
    "refresh":"eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ0b2tlbl90eXBlIjoicmVmcmVzaCIsImV4cCI6MTY1NjM3OTY4OSwiaWF0IjoxNjU2MjkzMjg5LCJqdGkiOiI2ZDcwMjQ5N2VjYTE0ZmQ0YjQzMjM5YzMzNDQ5NjNiMiIsInVzZXJfaWQiOjl9.0lB2EG0DjDjIiZt2OqBuUjy1Zw8c71uCOHf-UMTHY2I"  
}

resposta:

{
    "access": "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ0b2tlbl90eXBlIjoiYWNjZXNzIiwiZXhwIjoxNjU2Mjk3NDQxLCJpYXQiOjE2NTYyOTMyODksImp0aSI6ImY1YjNhOWY2ZDYzYzRjOWY4Yjc5ZWFkODRkNTJiMzEyIiwidXNlcl9pZCI6OX0.SPNTGHdXwGwVod-1VZLSJvRIRo5mIECk6brbTqwOE34"
}

correto - 200

errado - 401


---------------------------------------------------------

url: login/verify/

tipo: POST

função: Verificar se o token é vaildo

pedido:

{
    "token":"eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ0b2tlbl90eXBlIjoiYWNjZXNzIiwiZXhwIjoxNjU2Mjk2ODg5LCJpYXQiOjE2NTYyOTMyODksImp0aSI6Ijg1YzM3YWJiOTZjNTQ0Y2U4M2M2ZmY5MzBiMTgwMTdjIiwidXNlcl9pZCI6OX0.-C5f3KhAUgN_udTNjgQtTEIYqc80zFmafsjb19nHshc" 
}

resposta:


correto - 200

errado - 401






