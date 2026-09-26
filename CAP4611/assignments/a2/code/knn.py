"""
Implementation of k-nearest neighbours classifier
"""

import numpy as np

import utils
from utils import euclidean_dist_squared


class KNN:
    X = None
    y = None

    def __init__(self, k):
        self.k = k

    def fit(self, X, y):
        self.X = X  # just memorize the training data
        self.y = y

    def predict(self, X_hat):
        '''
        Personal notes on the function:
        
        :param X_hat: set of new points we want predictions for

        self.X is the matrix of training features
        self.y = training labels
        '''
        distances = euclidean_dist_squared(self.X, X_hat)
        predictions = [] # list to hold the predictions

        for i in range(X_hat.shape[0]):
            cur_distances = distances[:, i]
            nearest_points = np.argsort(cur_distances)[:self.k]
            nearest_labels = self.y[nearest_points]

            prediction = utils.mode(nearest_labels)
            predictions.append(prediction)

        return np.array(predictions)
    

if __name__ == "__main__":
    test = KNN(k=3)

    X = np.array([
        [1, 2], [3, 4], [5, 1]
    ])

    y = np.array([0, 1, 0])
    test.fit(X, y)
    print(test.X)
    print(X.shape)
