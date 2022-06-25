from numpy import insert
from pyrsistent import field
from rest_framework import serializers
from backend import models

class User(serializers.ModelSerializer):
    class Meta:
        model = models.User
        fields = ['id','username','name','password','birthday','email','type']
        extra_kwargs = {'password':{'write_only':True}}



class Option(serializers.ModelSerializer):
    class Meta:
        model = models.Option
        fields = ['id','answer','question','correct']


class Content(serializers.ModelSerializer):
    class Meta:
        model = models.Content
        fields = ['id','question','order','type',]


class LoadQuestion(serializers.ModelSerializer):
    author = serializers.StringRelatedField(read_only= True)
    options = Option(many=True, read_only=True)
    contents = Content(many=True, read_only=True)
    class Meta:
        model = models.Question
        fields = ['id','author','title','type','score','dificulty','minage','options','contents',]


class SaveQuestion(serializers.ModelSerializer):
    options = Option(many=True)
    contents = Content(many=True)
    class Meta:
        model = models.Question
        fields = ['id','author','title','type','score','dificulty','minage','options','contents']
    
    def create(self, validated_data):
        contents = validated_data.pop('contents')
        options = validated_data.pop('options')
        question = models.Question.objects.create(**validated_data)
        
        for option in options:
            models.Option.objects.create(question=question, **option)

        for content in contents:
            models.Content.objects.create(question=question,**content)
        
        
        
        return question



class SaveHistory(serializers.ModelSerializer):
    class Meta:
        model = models.History
        fields = ['id','player','question','date','correct','answer']
        read_only = ['correct','date']


class LoadHistory(serializers.ModelSerializer):
    player = serializers.StringRelatedField(read_only= True)
    class Meta:
        model = models.History
        fields = ['id','player','question','date','correct','answer']
        read_only = ['correct','date']
        
