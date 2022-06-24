from django.urls import path
from backend import views

from django.conf import settings
from django.conf.urls.static import static


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
    path('option/', views.option),
    path('content/', views.content),
]

urlpatterns += static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)