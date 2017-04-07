<div class="question">
    <a href="@@questions/view_question/{{$question->getId()}}@@"> {{ $question->getTitle() }}</a>
    <br />
    Posted: {{ $question->getDate() }} by <a href="@@user/view_user/{{ $question->getUserId() }}@@">{{ User::getFullName($question->getUserId()) }}</a>
    <br />
    %% views/tags_view.inc %%
    <p class="question-content"> {{ markdown(html_entity_decode(substr($question->getContent(), 0, 240)."...")) }}</p>
</div>