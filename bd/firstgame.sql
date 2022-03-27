use ComputationalMind;



insert into Author(Id, Name, Password, Email) values
				   ('CM','CM','1234','cm@gmail.com');

insert into Player(Id, Name, Password, Birthday, Email, Score) values
				  ('player1','player1','1234',Date('1980-12-12'),'player1@gmail.com','0');	

insert into Question(Author, Title, Type) values
					('CM','Codigo Secreto','SA');

insert into ComputationalMind.Option(Question,Answer,Correct) values
				                    ('1','Ola Mundo','1'),
                                    ('1','As armas e baroes assinalados','0'),
                                    ('1','oh mar salgado quanto do teu sal são lágrimas portugal','0'),
                                    ('1','Hello World','0');


insert into Content(Question, Content.Order, Type, Media) values
				   ('1','1','T','caminho_do_documento');

select * from Author;
select * from Player;

select * from Question as Q
inner join Content as C
on C.Question = Q.Id 
inner join ComputationalMind.Option as O
on O.Question=Q.Id; 












