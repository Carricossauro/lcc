from django.urls import path
from backend import views


urlpatterns = [
    path('', views.home),
    path('authors/', views.authors),
    path('authors/<str:id>', views.author),
    path('players/', views.players),
    path('players/<str:id>',views.player),
    path('questions/',views.questions),
    path('questions/<int:id>',views.question),
    path('history/',views.history),
    path('history/player/<str:player>',views.historyPlayer),
    path('history/question/<int:question>',views.historyQuestion),

]