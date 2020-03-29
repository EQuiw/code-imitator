from keras.models import Sequential
# from keras.layers import Convolution2D, MaxPooling2D
from keras.layers import Activation, Dropout, Dense
from keras import regularizers

from keras.wrappers.scikit_learn import KerasClassifier
from keras.utils.np_utils import to_categorical
from sklearn.utils import shuffle

from sklearn import preprocessing
from sklearn.model_selection import ParameterGrid
from sklearn.base import clone
import numpy as np
import time

from ConfigurationLearning.ConfigurationLearning import ConfigurationLearning


############# ######################## ######################## ########################


def _my_keras_model(input_dim_eq, output_dim_eq, neurons_eq, dropout_eq, optimizer_eq):
    """
    The heart of my attack -- the neural net model.
    :return: the model, a training history object
    """
    activation = "relu"
    w2 = 0.0

    # Model Definition
    model = Sequential()
    model.add(Dense(neurons_eq[0], input_shape=(input_dim_eq,), kernel_regularizer=regularizers.l2(w2) )) #
    model.add(Activation(activation))
    model.add(Dropout(dropout_eq))

    # Create more layers..
    if len(neurons_eq)>1:
        for nn in range(1,len(neurons_eq)):
            model.add(Dense(neurons_eq[nn], kernel_regularizer=regularizers.l2(w2)))  #
            model.add(Activation(activation))
            model.add(Dropout(dropout_eq))
            # print("Add",nn+1,". layer with:",Neurons[nn])

    model.add(Dense(output_dim_eq, name="before_softmax"))
    model.add(Activation('softmax'))

    # 3) train and eval
    model.compile(loss='categorical_crossentropy',
                  optimizer=optimizer_eq,  # rmsprop
                  metrics=['accuracy'])

    return model


def customized_grid_search_dnn(param_grid: dict, clf, listoftraintestsplits):

    accuracy_per_param: list = []
    params_list: list = [params for params in ParameterGrid(param_grid)]
    for params in params_list:
        cv_results = []
        cv_times = []
        #print(params)

        for x_train_cv, x_test_cv, y_train_cv, y_test_cv in listoftraintestsplits:
            #print(x_train_cv.shape)

            clf_copy = clone(clf)
            clf_copy.set_params(**params)

            input_dim_eq = x_train_cv.shape[1]
            output_dim_eq = y_train_cv.shape[1]
            dimsparams = dict(input_dim_eq = input_dim_eq, output_dim_eq = output_dim_eq)
            clf_copy.set_params(**dimsparams)

            time1 = time.time()
            clf_copy.fit(x_train_cv, y_train_cv)
            ypred_cv = clf_copy.predict(x_test_cv)
            time2 = time.time()
            cv_times.append( (time2-time1)*1000.0 )

            theaccuracy: np.float64 = np.mean(np.argmax(y_test_cv, axis=1) == ypred_cv)
            cv_results.append(theaccuracy)
        print("{1} (mean:{2}) by {0} (time: {3:.3f} ms)".format(params, cv_results, np.mean(np.array(cv_results)),
                                                             np.mean(np.array(cv_times))))
        accuracy_per_param.append((np.mean(np.array(cv_results)), np.sqrt(np.var(np.array(cv_results)))))

    best_param_index: int = np.argmax(np.array([x[0] for x in accuracy_per_param]))
    print("Best param:", params_list[best_param_index], " with ", accuracy_per_param[best_param_index])

    return params_list[best_param_index], accuracy_per_param[best_param_index]



def neural_network_learning(x_train, y_train, x_test, y_test, listoftraintestsplits,
                            config_learning: ConfigurationLearning, num_classes: int):

    # A. Preprocessing
    for i in range(len(listoftraintestsplits)):
        sc = preprocessing.StandardScaler().fit(listoftraintestsplits[i][0].todense())
        listoftraintestsplits[i][0] = sc.transform(listoftraintestsplits[i][0].todense())
        listoftraintestsplits[i][1] = sc.transform(listoftraintestsplits[i][1].todense())

        listoftraintestsplits[i][2] = to_categorical(listoftraintestsplits[i][2], num_classes=num_classes)
        listoftraintestsplits[i][3] = to_categorical(listoftraintestsplits[i][3], num_classes=num_classes)

        listoftraintestsplits[i][0], listoftraintestsplits[i][2] = shuffle(listoftraintestsplits[i][0],
                                                                           listoftraintestsplits[i][2],
                                                                           random_state=31 * 9)
        listoftraintestsplits[i][1], listoftraintestsplits[i][3] = shuffle(listoftraintestsplits[i][1],
                                                                           listoftraintestsplits[i][3],
                                                                           random_state=31 * 9)


    sc = preprocessing.StandardScaler().fit(x_train.todense())
    x_train = sc.transform(x_train.todense())
    x_test = sc.transform(x_test.todense())

    y_train_c = to_categorical(y_train, num_classes=num_classes)
    y_test_c = to_categorical(y_test, num_classes=num_classes)

    x_train, y_train_c = shuffle(x_train, y_train_c, random_state=31*5)
    x_test, y_test_c, y_test = shuffle(x_test, y_test_c, y_test, random_state=31*7)


    # B. Grid search to get best params
    # activation = ['relu', 'tanh', 'sigmoid']

    if config_learning.hyperparameters is None:
        neurons_eq = [(25, 25), (25, 25, 25), (50, 50), (50, 50, 50), (100, 100), (100, 100, 100), (175, 175),
                      (175, 175, 175),
                      (200, 200), (200, 200, 200), (300, 300)]
        param_grid = {"optimizer_eq": ['RMSprop'],  # ['SGD', 'RMSprop', 'Adagrad', 'Adadelta', 'Adam'],
                  "epochs": [100, 200, 300, 400, 500],
                  "neurons_eq": neurons_eq, #50
                  "dropout_eq": [0, 0.01, 0.1, 0.25, 0.5],
                  }
    else:
        param_grid = config_learning.hyperparameters


    kerasclf = KerasClassifier(build_fn=_my_keras_model, batch_size=20,
                            verbose=0)
    best_params, best_params_acc = customized_grid_search_dnn(param_grid=param_grid,
                                                          clf=kerasclf,
                                                          listoftraintestsplits=listoftraintestsplits)


    # C. Learn on best params
    clf_best = KerasClassifier(build_fn=_my_keras_model, batch_size=30,
                            input_dim_eq=x_train.shape[1],
                            output_dim_eq=y_train_c.shape[1],
                            verbose=0)
    clf_best.set_params(**best_params)
    clf_best.fit(x_train, y_train_c)

    acc = np.mean(np.argmax(y_test_c, axis=1) == clf_best.predict(x_test))

    print("DNN-Acc:", acc)
    return acc, clf_best, sc
