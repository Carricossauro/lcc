from django.urls import path
from backend import views

from django.conf import settings
from django.conf.urls.static import static


urlpatterns = [
    path('', views.home),
    path('users/', views.users),
    path('users/<str:username>', views.user),
    path('questions/',views.questions),
    path('questions/<int:id>',views.question),
    path('history/',views.history),
    path('history/player/<str:player>',views.historyPlayer),
    path('history/question/<int:question>',views.historyQuestion),
    path('login/', views.login)
]

urlpatterns += static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)