%% views/header.inc %%

<h1> {{ isset($title) ? $title : '' }}</h1>
<h3>{{ isset($subtitle) ? $subtitle : '' }}</h3>

<!-- outer row loop -->
<?php foreach ($questions as $question): ?>
    <div class="question">
        <a href="@@questions/view_question/{{$question->getId()}}@@"> {{ $question->getTitle() }}</a>
        <br />
        Posted: {{ $question->getDate() }} by <a href="@@user/view_user/{{ $question->getUserId() }}@@">{{ $question->getAuthorName() }}</a>
        <br />
        %% views/tags_view.inc %%
        <p class="question-content"> {{ substr($question->getContent(), 0, 240).".." }}</p>
    </div>
<?php endforeach ?>

<br />

[[ if (isLoggedIn()) : ]]
    <a href="@@questions/post_question/{{ isset($tag) ? $tag : '' }}@@">{{ $newQuestionButtonText }}</a>
[[ endif; ]]

%% views/footer.inc %%