from django.urls import path
from cm.views import home, authors, front



urlpatterns = [
    path('', home),
    path('authors/', authors),
    path('front/', front),
]