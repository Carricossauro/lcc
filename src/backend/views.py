
from django.http import HttpResponse
from django.shortcuts import render, get_object_or_404
from rest_framework.decorators import api_view
from rest_framework.response import Response
from backend import models
from backend import serializers
from datetime import datetime
from rest_framework.authentication import SessionAuthentication, BasicAuthentication
from rest_framework.permissions import IsAuthenticated
from backend import permissions

from rest_framework.views import APIView

# Create your views here.


class insertUsers(APIView):
    def post(self, request):
        serializer = serializers.User(data=request.data)
        serializer.is_valid(raise_exception=True)
        instance = serializer.save()
        instance.set_password(instance.password)
        instance.save()
        instance = serializer.validated_data
        instance.pop('password')
        return Response(instance, status=201)


class getUser(APIView):
    permission_classes = (IsAuthenticated, )
    def get(self, request, username):
        user = get_object_or_404(models.User.objects.filter(username=username))
        serializer = serializers.User(instance=user)
        return Response(serializer.data)



class getQuestions(APIView):
    def get(self, request):
        questions = models.Question.objects.all()
        serializer = serializers.LoadQuestion(instance=questions,many=True)
        self.check_object_permissions(request,serializer)
        return Response(serializer.data)
    
    
class insertQuestion(APIView):
    permission_classes = (IsAuthenticated,)
    def post(self, request):
        data = request.data
        if 'author' in request.data:
            author = get_object_or_404(models.User.objects.filter(username=data['author']))
            author = serializers.User(instance=author)
            author = author.data
            data.update({'author':author['id']})
        serializer = serializers.SaveQuestion(data=data)
        serializer.is_valid(raise_exception=True)
        serializer.save()
        return Response(serializer.data, status=201)



class updateQuestion(APIView):
    permission_classes = (permissions.QuestionIsOwner, IsAuthenticated)
    def post(self, request, id):
        question = get_object_or_404(models.Question.objects.filter(id=id))
        serializer = serializers.LoadQuestion(instance=question)
        self.check_object_permissions(request,serializer.data)
        question.delete()
        data = request.data
        if 'author' in request.data:
            author = get_object_or_404(models.User.objects.filter(username=data['author']))
            author = serializers.User(instance=author)
            author = author.data
            data.update({'author':author['id']})
        serializer = serializers.SaveQuestion(data=data)
        serializer.is_valid(raise_exception=True)
        serializer.save()
        return Response(serializer.data, status=201)



class insertHistory(APIView): 
    permission_classes = (IsAuthenticated,permissions.IsPlayer) 
    def post(self, request):
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
                self.check_object_permissions(request,data)
                data.update({'player':player['id']})

        if 'date' not in data:
            formatted_date = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
            data.update({'date':str(formatted_date)})
        
        serializer = serializers.SaveHistory(data=data)
        serializer.is_valid(raise_exception=True)
        serializer.save()
        return Response(serializer.data, status=201)




class historyPlayer(APIView):
    permission_classes = (IsAuthenticated,) 
    def get(self, request, player):
        player = models.User.objects.get(username=player)
        if player:
            player = serializers.User(instance=player)
            player = player.data
            player = player['id']
        else:
            return Response(status=404)
        history = models.History.objects.filter(player=player)
        print(history)
        serializer = serializers.LoadHistory(instance=history,many=True)
        result = serializer.data
        return Response(result)


class historyQuestion(APIView):
    permission_classes = (IsAuthenticated,) 
    def get(self, request, question):
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
