from django.urls import path
from backend import views

from django.conf import settings
from django.conf.urls.static import static

from rest_framework_simplejwt.views import (
    TokenObtainPairView,
    TokenRefreshView,
    TokenVerifyView,
)


urlpatterns = [
    path('users/', views.insertUsers.as_view()),
    path('users/<str:username>', views.getUser.as_view()),
    path('questions/',views.getQuestions.as_view()),
    path('questions/<int:id>',views.getQuestion.as_view()),
    path('questions/update/<int:id>',views.updateQuestion.as_view()),
    path('questions/insert/',views.insertQuestion.as_view()),
    path('history/',views.insertHistory.as_view()),
    path('history/player/<str:player>',views.historyPlayer.as_view()),
    path('history/question/<int:question>',views.historyQuestion.as_view()),
    path('login/', TokenObtainPairView.as_view(), name='token_obtain_pair'),
    path('login/refresh/', TokenRefreshView.as_view(), name='token_refresh'),
    path('login/verify/', TokenVerifyView.as_view(), name='token_verify'),

]

urlpatterns += static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)