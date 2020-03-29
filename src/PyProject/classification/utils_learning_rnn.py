from keras.models import Sequential, load_model
from keras.layers import Dense, Activation, Embedding, Dropout, TimeDistributed
from keras.layers import LSTM
from keras.optimizers import Adam, RMSprop
from keras.utils import to_categorical
from sklearn import preprocessing
from keras.utils.np_utils import to_categorical
from keras.wrappers.scikit_learn import KerasClassifier
from sklearn.utils import shuffle
import keras.optimizers
from sklearn.model_selection import ParameterGrid
from keras import regularizers
import numpy as np
import time
from keras import backend as K
from sklearn.ensemble import RandomForestClassifier
import sklearn.base
import keras.callbacks

from ConfigurationLearning.ConfigurationLearningRNN import ConfigurationLearningRNN


def my_model(input_dim_eq, output_dim_eq, denseneurons=128, lstmlayersno=1, denselayersno=3, optimizer=RMSprop(), nounits=32,
             dropout=0, l2reg=0, verbose=False):
    activation = "relu"
    input_shape_lstm = (1, input_dim_eq)
    lstmlayersno -= 1
    assert denselayersno>=2
    denselayersno -= 2

    model = Sequential()

    return_seq_first = False if lstmlayersno == 0 else True
    model.add(LSTM(nounits, return_sequences=return_seq_first,
                   input_shape=input_shape_lstm, dropout=dropout))
    if lstmlayersno >= 1:
        for l in range(lstmlayersno):
            return_seq_last = False if l == (lstmlayersno - 1) else True
            model.add(LSTM(nounits, return_sequences=return_seq_last, dropout=dropout))

    if denselayersno >= 1:
        for l in range(denselayersno):
            model.add(Dense(denseneurons, kernel_regularizer=regularizers.l2(l2reg)))
            model.add(Activation(activation))


    model.add(Dense(round(denseneurons*0.8), name="deep_representation", kernel_regularizer=regularizers.l2(l2reg)))
    model.add(Activation(activation))
    model.add(Dense(output_dim_eq, name="before_softmax", kernel_regularizer=regularizers.l2(l2reg)))
    model.add(Activation('softmax'))

    model.compile(loss='categorical_crossentropy', optimizer=optimizer,
                  metrics=['accuracy', 'categorical_accuracy'])

    if verbose is True:
        print(model.summary())

    return model


def r_neural_network_learning(x_train, y_train, x_test, y_test, listoftraintestsplits,
                              config_learning: ConfigurationLearningRNN, num_classes: int):

    # A. Preprocessing
    for i in range(len(listoftraintestsplits)):
        if config_learning.scale:
            sc = preprocessing.StandardScaler().fit(listoftraintestsplits[i][0].todense())
            listoftraintestsplits[i][0] = sc.transform(listoftraintestsplits[i][0].todense())
            listoftraintestsplits[i][1] = sc.transform(listoftraintestsplits[i][1].todense())
        else:
            listoftraintestsplits[i][0] = np.array(listoftraintestsplits[i][0].todense())
            listoftraintestsplits[i][1] = np.array(listoftraintestsplits[i][1].todense())

        listoftraintestsplits[i].append(to_categorical(listoftraintestsplits[i][2], num_classes=num_classes))
        listoftraintestsplits[i].append(to_categorical(listoftraintestsplits[i][3], num_classes=num_classes))

        # listoftraintestsplits[i][0], listoftraintestsplits[i][2] = shuffle(listoftraintestsplits[i][0],
        #                                                                    listoftraintestsplits[i][2],
        #                                                                    random_state=31 * 9)
        # listoftraintestsplits[i][1], listoftraintestsplits[i][3] = shuffle(listoftraintestsplits[i][1],
        #                                                                    listoftraintestsplits[i][3],
        #                                                                    random_state=31 * 9)

        trainsplitshape = (listoftraintestsplits[i][0].shape[0], 1, listoftraintestsplits[i][0].shape[1])
        testsplitshape = (listoftraintestsplits[i][1].shape[0], 1, listoftraintestsplits[i][1].shape[1])

        listoftraintestsplits[i][0] = listoftraintestsplits[i][0].reshape(trainsplitshape)
        listoftraintestsplits[i][1] = listoftraintestsplits[i][1].reshape(testsplitshape)

    assert len(listoftraintestsplits[0])==6
    if config_learning.scale:
        sc = preprocessing.StandardScaler().fit(x_train.todense())
        x_train = sc.transform(x_train.todense())
        x_test = sc.transform(x_test.todense())
    else:
        sc = None
        x_train = np.array(x_train.todense())
        x_test = np.array(x_test.todense())

    y_train_c = to_categorical(y_train, num_classes=num_classes)
    y_test_c = to_categorical(y_test, num_classes=num_classes)

    feature_dim = x_train.shape[1]
    x_train = x_train.reshape(x_train.shape[0], 1, x_train.shape[1])
    x_test = x_test.reshape(x_test.shape[0], 1, x_test.shape[1])

    # x_train, y_train_c = shuffle(x_train, y_train_c, random_state=31 * 5)
    # x_test, y_test_c, y_test = shuffle(x_test, y_test_c, y_test, random_state=31 * 7)

    # "optimizer": ['RMSprop'],  # ['SGD', 'RMSprop', 'Adagrad', 'Adadelta', 'Adam'],
    if config_learning.hyperparameters is None:
        param_grid = {
                      "RNN_epochs": [100, 200, 300, 350, 450, 500], #350], #50],
                      "RNN_nounits": [32, 128, 196, 256, 288], #, feature_dim],
                      "RNN_dropout": [0.6],
                      "RNN_lstmlayersno": [3],
                      "RNN_denselayersno": [3],
                      "RNN_l2reg": [0.00001],
                      "RNN_denseneurons": [round(0.45*feature_dim)]
                      }
    else:
        param_grid = config_learning.hyperparameters
        param_grid['RNN_denseneurons'] = [round(x * feature_dim) for x in param_grid['RNN_denseneurons']]

    if config_learning.cv_optimize_rlf_params:
        param_grid_rf = {"RF_n_estimators": [250],
                      "RF_max_features": [0.3, 0.6, 'auto'],
                      "RF_max_depth": [10, 25, 50, 75, None],
                      "RF_min_samples_leaf": [6, 12, 1],
                      }
        param_grid.update(param_grid_rf)



    kerasclf = KerasClassifier(build_fn=my_model, batch_size=128, input_dim_eq=feature_dim, output_dim_eq=num_classes,
                               optimizer="Adam", verbose=0)

    best_params_, best_params_acc = customized_grid_search_rnn(param_grid=param_grid,
                                                              clf=kerasclf,
                                                              listoftraintestsplits=listoftraintestsplits,
                                                               cv_use_rnn_output=config_learning.cv_use_rnn_output,
                                                               noofparallelthreads=config_learning.noofparallelthreads)
    best_params_rnn, best_params_rf = split_params_into_rnn_rf(params=best_params_)

    early_stop = keras.callbacks.EarlyStopping(monitor="loss", patience=20, verbose=1, min_delta=0.0)
    # param['callbacks'] = [early_stop]
    # param['validation_data'] = (x_test.reshape(x_test.shape[0], feature_dim, 1), y_test_c)

    # C. Learn on best params
    clf_best = KerasClassifier(build_fn=my_model, batch_size=128,
                               input_dim_eq=feature_dim, output_dim_eq=num_classes,
                               optimizer=keras.optimizers.Adam(lr=10e-4),
                               callbacks=[early_stop],
                               verbose=1)
    clf_best.set_params(**best_params_rnn)
    rnnhist = clf_best.fit(x_train, y_train_c)

    rnnacc: float = np.mean(np.argmax(y_test_c, axis=1) == clf_best.predict(x_test))


    # D. Learn RF
    rlf_deep, rfaccuracy = compute_rlf_on_rnn(clf_best=clf_best, x_train=x_train, x_test=x_test,
                                              y_train=y_train, y_test=y_test, params=best_params_rf,
                                              noofparallelthreads=config_learning.noofparallelthreads)


    print("DNN-Acc: {}% // RF-Acc: {}%".format(round(rnnacc*100, 2), round(rfaccuracy*100, 2)))
    return rnnacc, clf_best, sc, rlf_deep, rfaccuracy, rnnhist


def split_params_into_rnn_rf(params: dict):
    params_rnn = {}
    params_rlf = {}
    for k, v in params.items():
        if k.startswith("RF_"):
            params_rlf[k[3:]] = v
        else:
            assert(k.startswith("RNN_"))
            params_rnn[k[4:]] = v
    return params_rnn, params_rlf


def compute_rlf_on_rnn(clf_best, x_train, x_test, y_train, y_test, params, noofparallelthreads):
    # D. Learn RF
    get_deep_features = K.function([clf_best.model.layers[0].input, K.learning_phase()],
                                   [clf_best.model.layers[-3].output])

    x_train_deep = get_deep_features([x_train, 0])[0]
    x_test_deep = get_deep_features([x_test, 0])[0]

    rlf_deep = RandomForestClassifier(random_state=41, n_jobs=noofparallelthreads)
    rlf_deep.set_params(**params)

    rlf_deep.fit(x_train_deep, y_train)
    ypred = rlf_deep.predict(x_test_deep)
    cmps: np.ndarray = (y_test == ypred)
    rfaccuracy: np.float64 = np.sum(cmps) / np.shape(ypred)[0]

    return rlf_deep, rfaccuracy



def customized_grid_search_rnn(param_grid: dict, clf, listoftraintestsplits: list, cv_use_rnn_output: bool, noofparallelthreads):

    accuracy_per_param: list = []
    params_list: list = [params for params in ParameterGrid(param_grid)]

    if len(params_list) == 1:
        print("Only one param combi. No need for grid search!")
        return params_list[0], None

    for params_ in params_list:
        cv_results = []
        cv_times = []
        #print(params)

        params_rnn, params_rf = split_params_into_rnn_rf(params=params_)

        for x_train_cv, x_test_cv, y_train_cv, y_test_cv, y_train_c_cv, y_test_c_cv in listoftraintestsplits:
            #print(x_train_cv.shape)

            clf_copy = sklearn.base.clone(clf)
            clf_copy.set_params(**params_rnn)

            input_dim_eq = x_train_cv.shape[2]
            output_dim_eq = y_train_c_cv.shape[1]
            ad = keras.optimizers.Adam(lr=10e-4)
            early_stop = keras.callbacks.EarlyStopping(monitor="loss", patience=20, verbose=1, min_delta=0.0)
            dimsparams = dict(input_dim_eq = input_dim_eq, output_dim_eq = output_dim_eq,
                              callbacks=[early_stop], optimizer=ad)
            clf_copy.set_params(**dimsparams)

            time1 = time.time()
            clf_copy.fit(x_train_cv, y_train_c_cv)

            if cv_use_rnn_output is True:
               ypred_cv = clf_copy.predict(x_test_cv)
               theaccuracy: np.float64 = np.mean(np.argmax(y_test_c_cv, axis=1) == ypred_cv)
            else:
                _, theaccuracy = compute_rlf_on_rnn(clf_best=clf_copy, x_train=x_train_cv, x_test=x_test_cv,
                                                          y_train=y_train_cv, y_test=y_test_cv, params=params_rf,
                                                    noofparallelthreads=noofparallelthreads)

            time2 = time.time()
            cv_times.append( (time2-time1)*1000.0 )

            cv_results.append(theaccuracy)
            del clf_copy
        print("{1} (mean:{2}) by {0} (time: {3:.3f} ms)".format(params_, cv_results, np.mean(np.array(cv_results)),
                                                             np.mean(np.array(cv_times))))
        accuracy_per_param.append((np.mean(np.array(cv_results)), np.sqrt(np.var(np.array(cv_results)))))

    best_param_index: int = np.argmax(np.array([x[0] for x in accuracy_per_param]))
    print("Best param:", params_list[best_param_index], " with ", accuracy_per_param[best_param_index])

    return params_list[best_param_index], accuracy_per_param[best_param_index]
