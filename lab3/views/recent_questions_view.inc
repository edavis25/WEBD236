%% views/header.inc %%

<h1> {{ isset($title) ? $title : '' }}</h1>
<h3>{{ isset($subtitle) ? $subtitle : '' }}</h3>

<!-- outer row loop -->
[[ foreach ($questions as $question): ]]
    %% views/question_preview.inc %%
[[ endforeach; ]]

<br />

[[ if (Authenticator::instance() -> can('question_create')) : ]]
    <a href="@@questions/post_question/{{ isset($prefillTag) ? $prefillTag : '' }}@@">{{ $newQuestionButtonText }}</a>
[[ endif; ]]

%% views/footer.inc %%