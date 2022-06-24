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
    
class Option(serializers.ModelSerializer):
    class Meta:
        model = models.Option
        fields = ['id','answer','question','correct']


class Content(serializers.ModelSerializer):
    class Meta:
        model = models.Content
        fields = ['id','question','order','type','media', 'text']
        extra_kwargs = {"media": {"required": False, "allow_null": True}}



class Question(serializers.ModelSerializer):
    options = Option(many=True, read_only=True)
    contents = Content(many=True, read_only=True)
    class Meta:
        model = models.Question
        fields = ['id','author','title','type','score','dificulty','minage','options','contents']
        



class History(serializers.ModelSerializer):
    class Meta:
        model = models.History
        fields = ['id','player','question','date','correct','answer']
        read_only = ['correct','date']
