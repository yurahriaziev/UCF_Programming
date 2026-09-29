#!/usr/bin/env python
import argparse
import os
import pickle
from pathlib import Path

import matplotlib.pyplot as plt
import numpy as np
from sklearn.neighbors import KNeighborsClassifier
from sklearn.tree import DecisionTreeClassifier

# make sure we're working in the directory this file lives in,
# for imports and for simplicity with relative paths
os.chdir(Path(__file__).parent.resolve())

# our code
from utils import load_dataset, plot_classifier, handle, run, main
from decision_stump import DecisionStumpInfoGain
from decision_tree import DecisionTree
from kmeans import Kmeans
from knn import KNN
from naive_bayes import NaiveBayes, NaiveBayesLaplace
from random_tree import RandomForest, RandomTree


@handle("1")
def q1():
    dataset = load_dataset("citiesSmall.pkl")

    X = dataset["X"]
    y = dataset["y"]
    X_test = dataset["Xtest"]
    y_test = dataset["ytest"]

    for k in [1, 3, 10]:
        model = KNN(k=k)
        model.fit(X, y)
        plot_classifier(model, X, y)
        plt.title(f"Model with k={k}")
        plt.savefig(f"../figs/knn_k{k}.png")

        # make prediction and get error based on training data
        y_hat = model.predict(X)
        training_error = np.mean(y_hat != y)

        # make prediction and get error based on test data
        y_test_hat = model.predict(X_test)
        test_error = np.mean(y_test_hat != y_test)

        print(f"Model with k={k}")
        print(f"Training error: {training_error}")
        print(f"Test error: {test_error}\n")



@handle("2")
def q2():
    dataset = load_dataset("ccdebt.pkl")
    X = dataset["X"]
    y = dataset["y"]
    X_test = dataset["Xtest"]
    y_test = dataset["ytest"]

    ks = list(range(1, 30, 4))
    
    cv_accs = []
    for k in ks:
        fold_accs = []

        n = X.shape[0]
        fold_size = n // 10
        for fold in range(10):
            start = fold * fold_size
            end = start + fold_size

            mask = np.ones(n, dtype=bool)
            mask[start:end] = False

            X_train = X[mask]
            y_train = y[mask]

            X_val = X[~mask]
            y_val = y[~mask]

            model = KNN(k=k)
            model.fit(X_train, y_train)

            y_val_hat = model.predict(X_val)
            val_acc = np.mean(y_val_hat == y_val)
            fold_accs.append(val_acc)

        cv_accs.append(float(np.mean(fold_accs)))

    print(f"ks: {ks}")
    print(f"cv_accs: {cv_accs}")

    test_accs = []
    for k in ks:
        model = KNN(k=k)
        model.fit(X, y)

        y_test_hat = model.predict(X_test)
        test_acc = float(np.mean(y_test == y_test_hat))

        test_accs.append(test_acc)

    print(test_accs)

    plt.plot(ks, cv_accs, marker='o', label='Cross Validation accuracy')
    plt.plot(ks, test_accs, marker='o', label='Test accuracy')

    plt.xlabel('k')
    plt.ylabel('Accuracy')
    plt.title('kNN Accuracy vs. k')
    plt.legend()

    plt.savefig('../figs/q2_cv_test_accuracy.png')

    # plotting training error vs k
    train_errors = []
    for k in ks:
        model = KNN(k=k)
        model.fit(X, y)

        y_train_hat = model.predict(X)
        train_error = float(np.mean(y_train_hat != y))
        train_errors.append(train_error)

    plt.figure()
    plt.plot(ks, train_errors, marker='o')
    plt.xlabel('k')
    plt.ylabel('Train error')
    plt.title('Training Error vs. k')
    plt.savefig('../figs/q2_training_error.png')



@handle("3.2")
def q3_2():
    dataset = load_dataset("newsgroups.pkl")

    X = dataset["X"].astype(bool)
    y = dataset["y"]
    X_valid = dataset["Xvalidate"]
    y_valid = dataset["yvalidate"]
    groupnames = dataset["groupnames"]
    wordlist = dataset["wordlist"]

    print(wordlist[72])
    indices = np.where(X[802])[0]
    print(wordlist[indices])
    print(groupnames[y[802]])



@handle("3.3")
def q3_3():
    dataset = load_dataset("newsgroups.pkl")

    X = dataset["X"]
    y = dataset["y"]
    X_valid = dataset["Xvalidate"]
    y_valid = dataset["yvalidate"]

    print(f"d = {X.shape[1]}")
    print(f"n = {X.shape[0]}")
    print(f"t = {X_valid.shape[0]}")
    print(f"Num classes = {len(np.unique(y))}")

    """CODE FOR Q3.4: Modify naive_bayes.py/NaiveBayesLaplace"""

    model = NaiveBayes(num_classes=4)
    model.fit(X, y)

    y_hat = model.predict(X)
    err_train = np.mean(y_hat != y)
    print(f"Naive Bayes training error: {err_train:.3f}")

    y_hat = model.predict(X_valid)
    err_valid = np.mean(y_hat != y_valid)
    print(f"Naive Bayes validation error: {err_valid:.3f}")


@handle("3.4")
def q3_4():
    dataset = load_dataset("newsgroups.pkl")

    X = dataset["X"]
    y = dataset["y"]
    X_valid = dataset["Xvalidate"]
    y_valid = dataset["yvalidate"]

    print(f"d = {X.shape[1]}")
    print(f"n = {X.shape[0]}")
    print(f"t = {X_valid.shape[0]}")
    print(f"Num classes = {len(np.unique(y))}")

    model = NaiveBayes(num_classes=4)
    model.fit(X, y)
    print("No smoothing")
    print(model.p_xy[:, 0])

    model_laplace = NaiveBayesLaplace(num_classes=4, beta=1)
    model_laplace.fit(X, y)
    print("Laplace smoothing, beta=1")
    print(model_laplace.p_xy[:, 0])

    model_laplace_massive = NaiveBayesLaplace(num_classes=4, beta=10000)
    model_laplace_massive.fit(X, y)
    print("Laplace massive, beta=10000")
    print(model_laplace_massive.p_xy[:, 0])



@handle("4")
def q4():
    dataset = load_dataset("vowel.pkl")
    X = dataset["X"]
    y = dataset["y"]
    X_test = dataset["Xtest"]
    y_test = dataset["ytest"]
    print(f"n = {X.shape[0]}, d = {X.shape[1]}")

    def evaluate_model(model):
        model.fit(X, y)

        y_pred = model.predict(X)
        tr_error = np.mean(y_pred != y)

        y_pred = model.predict(X_test)
        te_error = np.mean(y_pred != y_test)
        print(f"    Training error: {tr_error:.3f}")
        print(f"    Testing error: {te_error:.3f}")

    print('Decision tree info gain')
    evaluate_model(DecisionTree(max_depth=np.inf, stump_class=DecisionStumpInfoGain))

    print('Random tree')
    evaluate_model(RandomTree(max_depth=np.inf))

    print('Random forest')
    evaluate_model(RandomForest(num_trees=50, max_depth=np.inf))



@handle("5")
def q5():
    X = load_dataset("clusterData.pkl")["X"]

    model = Kmeans(k=4)
    model.fit(X)
    y = model.predict(X)
    plt.scatter(X[:, 0], X[:, 1], c=y, cmap="jet")

    fname = Path("..", "figs", "kmeans_basic_rerun.png")
    plt.savefig(fname)
    print(f"Figure saved as {fname}")


@handle("5.1")
def q5_1():
    X = load_dataset("clusterData.pkl")["X"]

    best_error = np.inf
    best_model = None
    for i in range(50):
        model = Kmeans(k=4)
        model.fit(X)

        y = model.predict(X)
        error = model.error(X, y, model.means)

        if error < best_error:
            best_error = error
            best_model = model

    print(f"Lowest error: {best_error}")
    y = best_model.predict(X)

    plt.figure()
    plt.scatter(X[:, 0], X[:, 1], c=y, cmap="jet")
    plt.title('Best k-means clustering with k=4')
    plt.savefig('../figs/kmeans_best_k4.png')



@handle("5.2")
def q5_2():
    X = load_dataset("clusterData.pkl")["X"]

    ks = range(1, 11)
    min_errors = []

    for k in ks:
        best_error = np.inf
        for i in range(50):
            model = Kmeans(k=k)
            model.fit(X)

            y = model.predict(X)
            error = model.error(X, y, model.means)

            if error < best_error:
                best_error = error
        min_errors.append(best_error)

    plt.figure()
    plt.plot(list(ks), min_errors, marker='o')
    plt.xlabel('k')
    plt.ylabel('Minimum k-means error')
    plt.title('K-means error vs. k')
    plt.savefig('../figs/kmeans_error_vs_k.png')



if __name__ == "__main__":
    main()
