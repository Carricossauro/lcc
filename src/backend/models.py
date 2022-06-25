# This is an auto-generated Django model module.
# You'll have to do the following manually to clean this up:
#   * Rearrange models' order
#   * Make sure each model has one field with primary_key=True
#   * Make sure each ForeignKey and OneToOneField has `on_delete` set to the desired behavior
#   * Remove `managed = False` lines if you wish to allow Django to create, modify, and delete the table
# Feel free to rename the models, but don't rename db_table values or field names.

from django.db import models
from django.contrib.auth.models import AbstractUser

class User(AbstractUser):
    TYPE = (('A','Author'),('P','Player'))
    name = models.CharField(max_length=75)  # Field name made lowercase.
    password = models.CharField(max_length=256)  # Field name made lowercase.
    email = models.CharField(max_length=75)  # Field name made lowercase.
    birthday = models.DateField(null=True)  # Field name made lowercase.
    type = models.CharField(max_length=20,choices=TYPE)
    
    USERNAME_FIELD = 'username'
    REQUIRED_FIELDS = []
    


class Question(models.Model):
    DIFICULTY =(('E','Easy'),('M','Medium'),('H','Hard'))
    TYPE =(('SA','Short Answer'),('MC','Multiple Choice'),('TF','True or False'))
    author = models.ForeignKey(User, models.DO_NOTHING)  # Field name made lowercase.
    title = models.CharField(max_length=45)  # Field name made lowercase.
    type = models.CharField(max_length=30, choices=TYPE)  # Field name made lowercase.
    score = models.IntegerField()  # Field name made lowercase.
    dificulty = models.CharField(max_length=20,choices=DIFICULTY)  # Field name made lowercase.
    minage = models.IntegerField()  # Field name made lowercase.

    class Meta:
        managed = True
        


class Option(models.Model):
    question = models.ForeignKey(Question, models.DO_NOTHING,related_name='options',null=True)  # Field name made lowercase.
    answer = models.TextField()  # Field name made lowercase.
    correct = models.BooleanField()  # Field name made lowercase.

    class Meta:
        managed = True
        


class History(models.Model):
    id = models.AutoField(db_column='Id', primary_key=True)  # Field name made lowercase.
    player = models.ForeignKey(User, models.DO_NOTHING)  # Field name made lowercase.
    question = models.ForeignKey(Question, models.DO_NOTHING)  # Field name made lowercase.
    date = models.DateTimeField()  # Field name made lowercase.
    correct = models.BooleanField()  # Field name made lowercase.
    answer = models.TextField()  # Field name made lowercase.

    class Meta:
        managed = True
        
        
class Content(models.Model):
    TYPE =(('A','Audio'),('T','Text'),('V','Video'))
    question = models.ForeignKey(Question, models.DO_NOTHING,related_name='contents', null=True)  # Field name made lowercase.
    order = models.IntegerField()  # Field name made lowercase.
    type = models.CharField(max_length=10,choices=TYPE)  # Field name made lowercase.
    media = models.FileField(blank=True)
    text = models.TextField(blank=True)

    class Meta:
        managed = True
        #unique_together = (('id', 'order'),)
        







