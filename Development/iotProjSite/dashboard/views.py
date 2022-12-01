from django.shortcuts import render

# Create your views here.
import json
# from urllib import request
from django.shortcuts import render
# from django.template import RequestContext
# from dashboard.models import Mode, State
# from rest_framework import viewsets,request
# from dashboard.serializers import ModeSerializer, StateSerializer

# Create your views here.
from django.http import HttpResponse


def index(request):
    return render(request,"dashboard/index.html")