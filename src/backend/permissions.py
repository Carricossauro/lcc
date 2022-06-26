from doctest import TestResults
from rest_framework import permissions

class IsOwner(permissions.BasePermission):
    def has_object_permission(self, request, view, obj):
        return str(obj.author) == request.user.username
        
    def has_permission(self, request, view):
        return super().has_permission(request, view)


class IsPlayer(permissions.BasePermission):
    def has_object_permission(self, request, view, obj):
        return request.user.type == 'P'
        
    def has_permission(self, request, view):
        return super().has_permission(request, view)


class IsAuthor(permissions.BasePermission):
    def has_object_permission(self, request, view, obj):
        return request.user.type == 'A'

    def has_permission(self, request, view):
        return super().has_permission(request, view)


