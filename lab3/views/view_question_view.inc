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
        <a href="##" class="delete-button">[ Delete ]</a>&nbsp;
        <div class="confirm-delete" style="display: none;"> 
            <a href="@@questions/delete_question/{{ $question->getId() }}@@"> yes</a> / <a href="##" class="delete-button">no</a>
        </div>
    </div>
    <br /><br /><hr /><br />
    <div id='file-upload'>
        <form action="@@file/add@@" method="post" enctype="multipart/form-data">
            <input type="hidden" name="question-id" value="{{$question->getId()}}" />
            <label for="file">Add an attachment file:</label><hr />
            <input type="file" name="file" /><br />
            <div class="center">
                <input class="float-right" type="submit" value="Upload" />
            </div>
        </form>
    </div>
    <br /><br />
[[ endif; ]]

%% views/files.inc %%
<!-- Comment to fix renderTemplate include bug -->
%% views/errors.inc %%

<br />
[[ if (Authenticator::instance() -> can('answer_create')) : ]]
    %% views/answer_form.inc %%
[[ endif; ]]

%% views/answer_view.inc %%
<!-- Comment to fix renderTemplate include bug -->
%% views/footer.inc %%


