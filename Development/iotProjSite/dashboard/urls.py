from django.urls import path

from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path('snoop/', views.snoop, name='snoop'),
    # path('home/', views.home, name='home'),
]