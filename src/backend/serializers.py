from wsgiref.validate import validator
from attr import field
from rest_framework import serializers
from backend import models

class Author(serializers.ModelSerializer):
    class Meta:
        model = models.Author
        fields = ['id','name','password','email']


class Player(serializers.ModelSerializer):
    class Meta:
        model = models.Player
        fields = ['id','name','password','birthday','email']
    



class Question(serializers.ModelSerializer):
    class Meta:
        model = models.Question
        fields = ['id','author','title','type','score','dificulty','minage','maxage']


class Option(serializers.ModelSerializer):
    class Meta:
        model = models.Option
        fields = ['id','answer']

class Content(serializers.ModelSerializer):
    class Meta:
        model = models.Content
        fields = ['order','type','media']

class History(serializers.ModelSerializer):
    class Meta:
        model = models.History
        fields = ['player','question','date','correct','answer']
