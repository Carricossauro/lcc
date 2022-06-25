from doctest import TestResults
from rest_framework import permissions

class QuestionIsOwner(permissions.BasePermission):
    def has_object_permission(self, request, view, obj):
        
        return obj['author'] == request.user.username
        
    
    def has_permission(self, request, view):
        return super().has_permission(request, view)


class IsPlayer(permissions.BasePermission):
    def has_object_permission(self, request, view, obj):
        print('--------------------------------')
        print(obj['player'])
        print(request.user.username)
        print(obj['player'] == request.user.username)
        print('--------------------------------')
        return obj['player'] == request.user.username
        
    
    def has_permission(self, request, view):
        return super().has_permission(request, view)