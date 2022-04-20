
from django.http import HttpResponse
from django.shortcuts import render, get_object_or_404
from rest_framework.decorators import api_view
from rest_framework.response import Response
from backend import models
from backend import serializers
from datetime import datetime

# Create your views here.

def home(request):
    return HttpResponse('HOME')


@api_view(http_method_names=['get','post'])
def authors(request):
    if request.method == 'GET':
        authors = models.Author.objects.all()
        serializer = serializers.Author(instance=authors,many=True)
        return Response(serializer.data)
    
    elif request.method == 'POST':
        serializer = serializers.Author(data=request.data)
        serializer.is_valid(raise_exception=True)
        serializer.save()
        return Response(serializer.validated_data, status=201)


@api_view()
def author(request,id):
    author = get_object_or_404(models.Author.objects.filter(id=id))
    serializer = serializers.Author(instance=author)
    return Response(serializer.data) 

@api_view(http_method_names=['get','post'])
def players(request):
    if request.method == 'GET':
        players = models.Player.objects.all()
        serializer = serializers.Player(instance=players,many=True)
        return Response(serializer.data)
    
    elif request.method == 'POST':
        serializer = serializers.Player(data=request.data)
        serializer.is_valid(raise_exception=True)
        serializer.save()
        return Response(serializer.validated_data, status=201)


@api_view()
def player(request,id):
    player = get_object_or_404(models.Player.objects.filter(id=id))
    serializer = serializers.Player(instance=player)
    return Response(serializer.data)




@api_view(http_method_names=['get','post'])
def questions(request):
    if request.method == 'GET':
        questions = models.Question.objects.all()
        serializer = serializers.Question(instance=questions,many=True)
        return Response(serializer.data)
    elif request.method == 'POST':
        serializer = serializers.Question(data=request.data)
        serializer.is_valid(raise_exception=True)
        serializer.save()
        return Response(serializer.data, status=201)


def getOptions(question):
    options = models.Option.objects.filter(question=question)
    serializer = serializers.Option(instance=options,many=True)
    return serializer.data

def getContents(question):
    contents = models.Content.objects.filter(question=question)
    serializer = serializers.Content(instance=contents,many=True)
    return serializer.data


@api_view()
def question(request,id):
    question = get_object_or_404(models.Question.objects.filter(id=id))
    serializer = serializers.Question(instance=question)
    return Response(serializer.data)

@api_view(http_method_names=['get','post'])
def history(request):
    if request.method == 'GET':
        history = models.History.objects.all()
        serializer = serializers.History(instance=history,many=True)
        return Response(serializer.data)
    
    elif request.method == 'POST':
        data = request.data
        if 'answer' in request.data and 'question' in request.data:
            correct = models.Option.objects.get(question=request.data['question'],correct=1 )
            if correct:
                correct = serializers.Option(instance=correct)
                correct = correct.data
                if request.data['answer'] == correct['answer']:
                    data.update({'correct':1})
                else:
                    data.update({'correct':0})
        if 'date' not in data:
            formatted_date = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
            data.update({'date':str(formatted_date)})
        serializer = serializers.History(data=data)
        serializer.is_valid(raise_exception=True)
        serializer.save()
        return Response(serializer.data, status=201)



@api_view()
def historyPlayer(request,player):
    if not models.Player.objects.filter(id=player):
        return Response(status=404)
    history = models.History.objects.filter(player=player)
    serializer = serializers.History(instance=history,many=True)
    result = serializer.data
    for r in result:
        r.pop('player')
    return Response(result)

@api_view()
def historyQuestion(request,question):
    if not models.Question.objects.filter(id=question):
        return Response(status=404)
    history = models.History.objects.filter(question=question)
    serializer = serializers.History(instance=history,many=True)
    result = serializer.data
    for r in result:
        r.pop('question')
    return Response(result)




    
