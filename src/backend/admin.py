from django.contrib import admin
from backend import models

admin.site.register(models.Author)
admin.site.register(models.Player)
admin.site.register(models.Question)
admin.site.register(models.Option)
admin.site.register(models.Content)
admin.site.register(models.History)

# Register your models here.
