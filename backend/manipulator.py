import MySQLdb
from pprint import pprint
from datetime import datetime


def getTable(table_name):
    table = []
    cursor.execute("SELECT *  FROM %s;" % table_name)
    data = cursor.fetchone()
    while data:
        table.append(data)
        data = cursor.fetchone()
    return table


def insertAuthor(Id, Name, Password, Email):
	sql = "INSERT INTO Author (Id, Name, Password, Email) VALUES (%s, %s, %s, %s)"
	val = (Id, Name, Password, Email)
	cursor.execute(sql, val)
	mysql.commit()

def deleteAuthor(Id):
	sql = f"DELETE FROM Author WHERE Id = \'{Id}\'"
	cursor.execute(sql)
	mysql.commit()


def insertPlayer(Id, Name, Password, Birthday, Email):
	sql = "INSERT INTO Player (Id, Name, Password, Birthday, Email) VALUES (%s, %s, %s, %s, %s)"
	val = (Id, Name, Password, Birthday, Email)
	cursor.execute(sql, val)
	mysql.commit()

def deletePlayer(Id):
	sql = f"DELETE FROM Player WHERE Id = \'{Id}\'"
	cursor.execute(sql)
	mysql.commit()

def insertQuestion(Author, Title, Type, Score, Dificulty, MinAge, MaxAge):
	sql = "INSERT INTO Question (Author, Title, Type, Score, Dificulty, MinAge, MaxAge) VALUES (%s, %s, %s, %s, %s, %s, %s)"
	val = (Author, Title, Type, Score, Dificulty, MinAge, MaxAge)
	cursor.execute(sql, val)
	mysql.commit()

def deleteQuestion(Id):
	sql = f"DELETE FROM Question WHERE Id = \'{Id}\'"
	cursor.execute(sql)
	mysql.commit()


def insertContent(Question, Order, Type, Media):
	sql = "INSERT INTO Author (Question, Order, Type, Media) VALUES (%s, %s, %s, %s)"
	val = (Question, Order, Type, Media)
	cursor.execute(sql, val)
	mysql.commit()

def deleteContent(Question, Order):
	sql = f"DELETE FROM Author WHERE Question = \'{Question}\' and Order = \'{Order}\'"
	cursor.execute(sql)
	mysql.commit()

def insertOption(Question, Answer, Correct):
	sql = "INSERT INTO ComputationalMind.Option(Question, Answer, Correct) VALUES (%s, %s, %s)"
	val = (Question, Answer, Correct)
	cursor.execute(sql, val)
	mysql.commit()

def deleteOption(Id):
	sql = f"DELETE FROM ComputationalMind.Option WHERE Id = \'{Id}\'"
	cursor.execute(sql)
	mysql.commit()


def insertHistory(Player, Question, Correct, Answer):
	now = datetime.now()
	formatted_date = now.strftime('%Y-%m-%d %H:%M:%S')
	sql = "INSERT INTO History(Player, Question, Date, Correct, Answer) VALUES (%s, %s, %s, %s, %s)"
	val = (Player, Question, formatted_date, Correct, Answer)
	cursor.execute(sql, val)
	mysql.commit()


def deleteHistory(Id):
	sql = f"DELETE FROM History WHERE Id = \'{Id}\'"
	cursor.execute(sql)
	mysql.commit()

def showBD():
	print('Author:')
	pprint(Author)
	print()
	print('Content:')
	pprint(Content)
	print()
	print('History:')
	pprint(History)
	print()
	print('Option:')
	pprint(Option)
	print()
	print('Player:')
	pprint(Player)
	print()
	print('Question:')
	pprint(Question)






# realizar no mysql
# CREATE USER 'admin'@'localhost' IDENTIFIED BY 'Adm1nas-';
# GRANT ALL ON ComputationalMind.* to 'admin'@'localhost';
# FLUSH PRIVILEGES;


user = "admin"
host = "localhost"
password = "Adm1nas-"
schema = "ComputationalMind"


if __name__ == '__main__':
    import sys
    if len(sys.argv) == 3:
        user = sys.argv[1]
        password = sys.argv[2]


mysql = MySQLdb.connect(host,user,password,schema)
cursor = mysql.cursor()

#insertAuthor('A1','Author2','1234','a2@gmail.com')
deleteAuthor('A1')

#insertPlayer('P1','Player1','1234','2020-01-01','p1@gmail.com')
#deletePlayer('P1')


#insertQuestion('A1','Codigo Secreto', 'SA','10','Medium','5','7')
#deleteQuestion(4)

#insertOption('3','Ola Mundo','1')
#deleteOption(5)


#insertHistory('P1','3','1','Ola Mundo')
#deleteHistory(1)


Author = getTable('Author')
Content = getTable('Content')
History = getTable('History')
Option = getTable('ComputationalMind.Option')
Player = getTable('Player')
Question = getTable('Question')

showBD()


cursor.close()
mysql.close()



