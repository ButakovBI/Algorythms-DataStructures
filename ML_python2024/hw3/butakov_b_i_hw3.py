import pandas as pd
import numpy as np
from sklearn.preprocessing import PolynomialFeatures, StandardScaler
from sklearn.linear_model import RidgeCV, LassoCV
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error
from sklearn.impute import SimpleImputer


train_data = pd.read_csv('Life_train.csv')
test_data = pd.read_csv('Life_test.csv')


train_data.columns = train_data.columns.str.strip()
test_data.columns = test_data.columns.str.strip()


X = train_data.drop(columns=['Life expectancy'])
y = train_data['Life expectancy']


medians = X.median()


X_imputed = X.fillna(medians)


scaler = StandardScaler()
X_scaled = scaler.fit_transform(X_imputed)


poly_features = PolynomialFeatures(degree=2, include_bias=False)
X_poly = poly_features.fit_transform(X_scaled)


X_train, X_val, y_train, y_val = train_test_split(X_poly, y, test_size=0.2, random_state=42)


ridge_model = RidgeCV(alphas=np.logspace(-4, 1, 50), cv=5)
ridge_model.fit(X_train, y_train)
y_val_pred_ridge = ridge_model.predict(X_val)
ridge_mse = mean_squared_error(y_val, y_val_pred_ridge)
print("Ridge Validation MSE:", ridge_mse)


lasso_model = LassoCV(alphas=np.logspace(-4, 1, 50), cv=5, max_iter=5000, random_state=42)
lasso_model.fit(X_train, y_train)
y_val_pred_lasso = lasso_model.predict(X_val)
lasso_mse = mean_squared_error(y_val, y_val_pred_lasso)
print("Lasso Validation MSE:", lasso_mse)


if ridge_mse < lasso_mse:
    final_model = ridge_model
else:
    final_model = lasso_model


final_val_mse = min(ridge_mse, lasso_mse)
print("Final Validation MSE:", final_val_mse)


X_test_imputed = imputer.transform(test_data)
X_test_scaled = scaler.transform(X_test_imputed)
X_test_poly = poly_features.transform(X_test_scaled)


y_test_pred = final_model.predict(X_test_poly)


submission = pd.DataFrame({
    "index": test_data.index,
    "Life expectancy": y_test_pred
})
submission.to_csv('submission.csv', index=False)
