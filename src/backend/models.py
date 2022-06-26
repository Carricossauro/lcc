

from django.db import models
from django.contrib.auth.models import AbstractUser

class User(AbstractUser):
    TYPE = (('A','Author'),('P','Player'))
    name = models.CharField(max_length=75)  
    password = models.CharField(max_length=256)  
    email = models.CharField(max_length=75)  
    birthday = models.DateField(null=True)  
    type = models.CharField(max_length=20,choices=TYPE)
    
    USERNAME_FIELD = 'username'
    REQUIRED_FIELDS = []
    


class Question(models.Model):
    DIFICULTY =(('E','Easy'),('M','Medium'),('H','Hard'))
    TYPE =(('SA','Short Answer'),('MC','Multiple Choice'),('TF','True or False'))
    author = models.ForeignKey(User, models.DO_NOTHING)  
    title = models.CharField(max_length=45)  
    type = models.CharField(max_length=30, choices=TYPE)  
    score = models.IntegerField()  
    dificulty = models.CharField(max_length=20,choices=DIFICULTY)  
    minage = models.IntegerField() 


    class Meta:
        managed = True
        


class Option(models.Model):
    question = models.ForeignKey(Question, models.DO_NOTHING,related_name='options',null=True) 
    answer = models.TextField()  
    correct = models.BooleanField()  

    class Meta:
        managed = True
        


class History(models.Model):
    id = models.AutoField(db_column='Id', primary_key=True)  
    player = models.ForeignKey(User, models.DO_NOTHING)  
    question = models.ForeignKey(Question, models.DO_NOTHING)  
    date = models.DateTimeField()  
    correct = models.BooleanField()  
    answer = models.TextField()  

    class Meta:
        managed = True
        
        
class Content(models.Model):
    TYPE =(('A','Audio'),('T','Text'),('V','Video'))
    question = models.ForeignKey(Question, models.DO_NOTHING,related_name='contents', null=True)  
    order = models.IntegerField() 
    type = models.CharField(max_length=10,choices=TYPE)  
    media = models.FileField(blank=True)
    text = models.TextField(blank=True)

    class Meta:
        managed = True
        #unique_together = (('id', 'order'),)
        







