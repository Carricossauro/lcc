
from django.http import HttpResponse
from django.shortcuts import render, get_object_or_404
from rest_framework.decorators import api_view
from rest_framework.response import Response
from backend import models
from backend import serializers
from datetime import datetime
from rest_framework.permissions import IsAuthenticated

# Create your views here.

def home(request):
    return HttpResponse('HOME')


@api_view(http_method_names=['get','post'])
def users(request):
    if request.method == 'GET':
        users = models.User.objects.all()
        serializer = serializers.User(instance=users,many=True)
        return Response(serializer.data)
    
    elif request.method == 'POST':
        serializer = serializers.User(data=request.data)
        serializer.is_valid(raise_exception=True)
        serializer.save()
        return Response(serializer.validated_data, status=201)


@api_view()
def user(request,username):
    user = get_object_or_404(models.User.objects.filter(username=username))
    serializer = serializers.User(instance=user)
    return Response(serializer.data) 




@api_view(http_method_names=['get','post'])
def questions(request):
    if request.method == 'GET':
        questions = models.Question.objects.all()
        serializer = serializers.LoadQuestion(instance=questions,many=True)
        return Response(serializer.data)
    
    
    elif request.method == 'POST':
        data = request.data
        if 'author' in request.data:
            author = models.User.objects.get(username=request.data['author'])
            author = serializers.User(instance=author)
            author = author.data
            if author:
                data.update({'author':author['id']})
        serializer = serializers.SaveQuestion(data=data)
        serializer.is_valid(raise_exception=True)
        serializer.save()
        return Response(serializer.data, status=201)
        



@api_view()
def question(request,id):
    question = get_object_or_404(models.Question.objects.filter(id=id))
    serializer = serializers.LoadQuestion(instance=question)
    return Response(serializer.data)




@api_view(http_method_names=['get','post'])
def history(request):
    if request.method == 'GET':
        history = models.History.objects.all()
        serializer = serializers.LoadHistory(instance=history,many=True)
        return Response(serializer.data)
    
    elif request.method == 'POST':
        data = request.data
        if 'answer' in request.data and 'question' in request.data:
            correct = models.Option.objects.get(question=request.data['question'],correct=True )
            if correct:
                correct = serializers.Option(instance=correct)
                correct = correct.data
                if request.data['answer'] == correct['answer']:
                    data.update({'correct':1})
                else:
                    data.update({'correct':0})
        if 'player' in request.data:
            player = models.User.objects.get(username=request.data['player'])
            player = serializers.User(instance=player)
            player = player.data
            if player:
                data.update({'player':player['id']})

        if 'date' not in data:
            formatted_date = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
            data.update({'date':str(formatted_date)})
        print(data)
        serializer = serializers.SaveHistory(data=data)
        serializer.is_valid(raise_exception=True)
        serializer.save()
        return Response(serializer.data, status=201)



@api_view()
def historyPlayer(request,player):
    player = models.User.objects.get(username=player)
    if player:
        player = serializers.User(instance=player)
        player = player.data
        player = player['id']
    else:
        return Response(status=404)
    history = models.History.objects.filter(player=player)
    serializer = serializers.LoadHistory(instance=history,many=True)
    result = serializer.data

    return Response(result)

@api_view()
def historyQuestion(request,question):
    if not models.Question.objects.filter(id=question):
        return Response(status=404)
    history = models.History.objects.filter(question=question)
    serializer = serializers.LoadHistory(instance=history,many=True)
    result = serializer.data
    return Response(result)

    
@api_view(http_method_names=['post'])
def login(request):
    data = request.data
    user = get_object_or_404(models.User.objects.filter(username=data["username"], type=data["type"]))
    if (user):
        user = serializers.Login(instance=user)
        user = user.data
        if user['password'] == data["password"] and user["type"] == data["type"]:
            return Response(status=201)
    return Response(status=404)
