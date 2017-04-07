%% views/header.inc %%

<h1>{{ $title }}</h1>
<hr />
<p>Posted on: {{$question->getDate()}} by <a href="@@user/view_user/{{ $question->getUserId() }}@@">{{ User::getFullName($question->getUserId()) }}</a></p>

%% views/tags_view.inc %%

<p class="question-content">{{ markdown(html_entity_decode($question->getContent())) }}</p>



<!-- Add edit/delete links if user is question author -->
[[ if ( $isAuthor || Authenticator::instance() -> can('question_edit')) : ]]
    <a href="@@questions/edit_question/{{ $question->getId() }}@@">[ Edit ]</a>
    <div class="delete-wrapper">
        <a href="#" class="delete-button">[ Delete ]</a>&nbsp;
        <div class="confirm-delete" style="display: none;"> 
            <a href="@@questions/delete_question/{{ $question->getId() }}@@"> yes</a> / <a href="#" class="delete-button">no</a>
        </div>
    </div>
    
    <br /><br />
[[ endif; ]]

<br />
[[ if (Authenticator::instance() -> can('answer_create')) : ]]
    %% views/answer_form.inc %%
[[ endif; ]]


[[ if ($answers && count($answers) > 0) : ]]
    <h2>Answers:</h2>
    [[ foreach($answers as $answer) : ]]
        %% views/answer_view.inc %%
    [[ endforeach; ]]   
[[ endif; ]]

%% views/footer.inc %%


