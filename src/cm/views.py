from django.http import HttpResponse
from django.shortcuts import render

from .models import Author
# Create your views here.

def home(request):
    return HttpResponse('HOME')

def authors(request):
    authors = Author.objects.all()
    output = '<br>'.join([f'Id: {a.id} Nome: {a.name}' for a in authors])
    return HttpResponse(output)

def front(request):
    context = { }
    return render(request, "index.html", context)
