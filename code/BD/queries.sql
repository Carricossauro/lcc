use ComputationalMind;


insert into Player (Id,Name,Password,Birthday,Email,Score ) values
					("god","carrico","1234",Date("2000-01-01"),"carrico@gmail.com","100");

insert into Author(Id,Name,Password,Email)values
				  ("PRH","Pedro Rangel","4321","prh@di.uminho.pt");
  
insert into Question(Author,Title,Type) values
					("PRH","Jogo do regex","SA");
                    
insert into Content(Question, Content.Order, Type, Media) values
				   (1, 1, "T","O que é uma expressao regular?"  );

update Content 
	set Media = "Diga uma epxressao para encontrar todas as palvaras só com o caracter a"
		where Question = 1;
                   
insert into ComputationalMind.Option(Question, Answer, Correct) values
									(1, "a*",1);
                                    

select Answer from ComputationalMind.Option where Question = 1;
 
select * from Player;

select * from Author;





