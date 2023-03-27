from flask import Flask, request, render_template, url_for
import numpy as np 
from sklearn.preprocessing import StandardScaler
import joblib as joblib 

model = joblib.load()