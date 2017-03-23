%% views/header.inc %%

<h1>{{ $title }}</h1>

<table>
    <tr>
        <td>First Name: </td>
        <td>{{ $user->getFirstName() }}</td>
    </tr>
    <tr>
        <td>Last Name: </td>
        <td>{{ $user->getLastName() }}</td>
    </tr>
    <tr>
        <td>E-mail: </td>
        <td>{{ $user->getEmail() }}</td>
    </tr>
</table>

<br />

[[ if ($ownsAccount) : ]]
<a href="@@user/edit_user/{{ $user->getId() }}@@">[Edit]</a>
<a href="#" onclick="toggle('confirm-delete')">[Delete]</a>
<div id="confirm-delete" style="display: none;">Are you sure? <a href="@@user/delete_user/{{ $user->getId() }}@@">yes</a> / <a href="#" onclick="toggle('confirm-delete')">no</a></div>
[[ endif; ]]

<h2>Questions By {{ $user->getFullName() }}</h2>

[[ foreach ($questions as $question): ]]
<div class="question">
    <a href="@@questions/view_question/{{$question->getId()}}@@"> {{ $question->getTitle() }}</a>
    <br />
    Posted: {{ $question->getDate() }} by <a href="@@user/view_user/{{ $question->getUserId() }}@@">{{ $question->getAuthorName() }}</a>
    <br />
    {{ ($question->getTags()) ? "Tags: " . $question->getTags() : '' }}

    <p class="question-content"> {{ substr($question->getContent(), 0, 240).".." }}</p>
</div>
[[ endforeach ]]

%% views/footer.inc %%