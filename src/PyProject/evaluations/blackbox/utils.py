import classification.utils_load_learnsetup
import classification.LearnSetups.LearnSetup


def compute_impersonation_pairs(batch_id, authorspairs, possible_authors, total_no_batches):
    authorspairs = __compute_pairs(batch_id=batch_id,
                                   authorspairs=authorspairs,
                                   possible_authors=possible_authors,
                                   total_no_batches=total_no_batches)
    possible_authors = list(set([x[0] for x in authorspairs] + [x[1] for x in authorspairs]))
    no_authors = len(possible_authors)

    return authorspairs, possible_authors, no_authors


def __compute_pairs(batch_id, authorspairs, possible_authors, total_no_batches):
    total = len(possible_authors) * (len(possible_authors)-1)

    range_authors = (int(total / total_no_batches * (batch_id - 1)), int(total / total_no_batches * batch_id))
    assert range_authors[0] >= 0
    assert range_authors[1] <= total
    return authorspairs[range_authors[0]:range_authors[1]]


def compute_dodging_pairs(batch_id, total_no_batches, learnmodelspath, feature_method, learn_method, problem_id, threshold_sel):

    # first, load all possible authors
    testlearnsetup_temp: classification.LearnSetups.LearnSetup.LearnSetup = classification.utils_load_learnsetup.load_learnsetup(
        learnmodelspath=learnmodelspath,
        feature_method=feature_method,
        learn_method=learn_method,
        problem_id=problem_id,
        threshold_sel=threshold_sel)

    return compute_dodging_pairs_preloaded_learnsetup(testlearnsetup=testlearnsetup_temp,
                                                      batch_id=batch_id,
                                                      total_no_batches=total_no_batches)


def compute_dodging_pairs_preloaded_learnsetup(testlearnsetup, batch_id, total_no_batches):

    possible_authors = testlearnsetup.data_final_test.getauthors().tolist()
    total = len(possible_authors)

    # now select the range of authors in current batch
    range_authors = (int(total / total_no_batches * (batch_id - 1)), int(total / total_no_batches * batch_id))
    assert range_authors[0] >= 0
    assert range_authors[1] <= total

    possible_authors = possible_authors[range_authors[0]:range_authors[1]]
    no_authors = len(possible_authors)
    authorspairs = None

    return authorspairs, possible_authors, no_authors

