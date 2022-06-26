
from click import option
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
import re

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
        return Response(serializer.data, status=201)

class profile(APIView):
    permission_classes = (IsAuthenticated, )
    def get(self,request):
        user = get_object_or_404(models.User.objects.filter(username=request.user.username))
        serializer = serializers.User(instance=user)
        return Response(serializer.data, status=201)



class getQuestions(APIView):
    permission_classes = (IsAuthenticated, )
    def get(self, request):
        questions = models.Question.objects.all()
        serializer = serializers.LoadQuestion(instance=questions,many=True)
        return Response(serializer.data,status=201)
    
class getQuestion(APIView):
    def get(self, request, id):
        question = get_object_or_404(models.Question.objects.filter(id=id))
        serializer = serializers.LoadQuestion(instance=question)
        return Response(serializer.data)
    
class insertQuestion(APIView):
    permission_classes = (IsAuthenticated,permissions.IsAuthor,)
    def post(self, request):
        data = request.data
        self.check_object_permissions(request,None)
        data.update({'author':request.user.id})
        serializer = serializers.SaveQuestion(data=data)
        serializer.is_valid(raise_exception=True)
        serializer.save()
        return Response(serializer.data, status=201)



class updateQuestion(APIView):
    permission_classes = (IsAuthenticated, permissions.IsOwner,)
    def put(self, request, id):
        question = get_object_or_404(models.Question.objects.filter(id=id))
        self.check_object_permissions(request,question)
        data = request.data
        data.update({'author':request.user.id})
        serializer = serializers.SaveQuestion(question,data=data)
        serializer.is_valid(raise_exception=True)
        serializer.save()
        return Response(serializer.data, status=201)



class insertHistory(APIView): 
    permission_classes = (IsAuthenticated,permissions.IsPlayer) 
    def post(self, request):
        self.check_object_permissions(request,None)
        data = request.data
        data.update({'correct':0})
        data.update({'player':request.user.id})
        formatted_date = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        data.update({'date':str(formatted_date)})

        if 'answer' in request.data and 'question' in request.data:
            option = get_object_or_404(models.Option.objects.filter(question=request.data['question'],correct=True))
            question = get_object_or_404(models.Question.objects.filter(id=request.data['question']))
            answer = option.answer
            type = question.type
            
            if type == 'SA' and bool(re.match(answer,request.data['answer'].strip())):
                data.update({'correct':1})
            elif request.data['answer'] == answer:
                data.update({'correct':1})
         
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
        serializer = serializers.LoadHistory(instance=history,many=True)
        result = serializer.data
        return Response(result, status=201)


class historyQuestion(APIView):
    permission_classes = (IsAuthenticated,) 
    def get(self, request, question):
        if not models.Question.objects.filter(id=question):
            return Response(status=404)
        history = models.History.objects.filter(question=question)
        serializer = serializers.LoadHistory(instance=history,many=True)
        result = serializer.data
        return Response(result, status=201)



