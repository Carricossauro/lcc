from rest_framework import serializers
from backend import models

class User(serializers.ModelSerializer):
    class Meta:
        model = models.User
        fields = ['id','username','name','password','birthday','email','type']
        extra_kwargs = {'password':{'write_only':True}}



class OptionForAuthor(serializers.ModelSerializer):
    id = serializers.IntegerField(required=False)
    class Meta:
        model = models.Option
        fields = ['id','answer','question','correct']
        

class OptionForPlayer(serializers.ModelSerializer):
    id = serializers.IntegerField(required=False)
    class Meta:
        model = models.Option
        fields = ['id','answer','question',]
        

class Content(serializers.ModelSerializer):
    id = serializers.IntegerField(required=False)
    class Meta:
        model = models.Content
        fields = ['id','question','order','type','text','media']


class LoadQuestionForAuthor(serializers.ModelSerializer):
    author = serializers.StringRelatedField(read_only= True)
    options = OptionForAuthor(many=True, read_only=True)
    contents = Content(many=True, read_only=True)
    class Meta:
        model = models.Question
        fields = ['id','author','title','type','score','dificulty','minage','options','contents',]

class LoadQuestionForPlayer(serializers.ModelSerializer):
    author = serializers.StringRelatedField(read_only= True)
    options = OptionForPlayer(many=True, read_only=True)
    contents = Content(many=True, read_only=True)
    class Meta:
        model = models.Question
        fields = ['id','author','title','type','score','dificulty','minage','options','contents',]


class SaveQuestion(serializers.ModelSerializer):
    options = OptionForAuthor(many=True)
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

    def update(self, instance, validated_data):
        contents = validated_data.pop('contents')
        options = validated_data.pop('options')
        instance.title = validated_data.get('title',instance.title)
        instance.type = validated_data.get('type', instance.type)
        instance.score = validated_data.get('score', instance.score)
        instance.dificulty = validated_data.get('dificulty',instance.dificulty)
        instance.minage = validated_data.get('minage',instance.minage)
        instance.save()
        keep_contents = []
        keep_options = []
        for content in contents:
            if 'id' in content.keys():
                if models.Content.objects.filter(id=content['id']).exists:
                    c = models.Content.objects.get(id=content['id'])
                    c.order = content.get('order',c.order)
                    c.type = content.get('type',c.type)
                    c.text = content.get('text',c.text)
                    c.media = content.get('media', c.media)
                    c.save()
                    keep_contents.append(c.id)
            else:
                c = models.Content.objects.create(question=instance,**content)
                keep_contents.append(c.id)

        for content in models.Content.objects.filter(question=instance.id):
            if content.id not in keep_contents:
                content.delete()
    
        for option in options:
            if 'id' in option.keys():
                if models.Option.objects.filter(id=option['id']).exists:
                    o = models.Option.objects.get(id=option['id'])
                    o.answer = option.get('answer',o.answer)
                    o.correct = option.get('correct',o.correct)
                    o.save()
                    keep_options.append(o.id)
            else:
                o = models.Option.objects.create(question=instance,**option)
                keep_options.append(o.id)
        
        for option in models.Option.objects.filter(question=instance.id):
            if option.id not in keep_options:
                option.delete() 
        return instance


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
        
