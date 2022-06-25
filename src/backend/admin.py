from django.contrib import admin
from backend import models



# Register your models here.

admin.site.register(models.User)
admin.site.register(models.Question)
admin.site.register(models.Option)
admin.site.register(models.Content)
admin.site.register(models.History)
