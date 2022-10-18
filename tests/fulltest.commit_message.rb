require 'minitest/spec'
require 'minitest/autorun'
require 'minitest/parallel'
require './scripts/commit_message_hook'

class CommitMessageHookTest < Minitest::Test
  def test_valid_feature_commit
    message = 'feat: awesome feature'
    response = CommitMessageHook.call(message)

    assert_equal true, response.fetch(:success)
    assert_equal [], response.fetch(:errors)
  end

  def test_valid_scoped_commit
    message = 'docs(readme): awesome docs'
    response = CommitMessageHook.call(message)

    assert_equal true, response.fetch(:success)
    assert_equal [], response.fetch(:errors)
  end

  def test_valid_breaking_changes_footer
    message = "chore!: drop support\n\nBREAKING CHANGE: drop support"
    response = CommitMessageHook.call(message)

    assert_equal true, response.fetch(:success)
    assert_equal [], response.fetch(:errors)
  end

  def test_must_ignore_comments
    message = "docs(readme): awesome docs\n# comments must be ignored"
    response = CommitMessageHook.call(message)

    assert_equal true, response.fetch(:success)
    assert_equal [], response.fetch(:errors)
  end

  def test_invalid_commit
    message = 'invalid commit'
    response = CommitMessageHook.call(message)

    assert_equal false, response.fetch(:success)
    assert_includes response.fetch(:errors), 'Invalid commit title format'
  end

  def test_invalid_size
    message = 'feat: commit title max characters are 80 characters, here we have more than 80, we have 90'
    response = CommitMessageHook.call(message)

    assert_equal false, response.fetch(:success)
    assert_includes response.fetch(:errors), 'Invalid commit title max size (80)'
  end

  def test_missing_semicolon
    message = 'feat awesome feature'
    response = CommitMessageHook.call(message)

    assert_equal false, response.fetch(:success)
    assert_includes response.fetch(:errors), 'Invalid commit title format'
  end

  def test_not_empty_second_line
    message = "feat: awesome feature\nmust be empty"
    response = CommitMessageHook.call(message)

    assert_equal false, response.fetch(:success)
    assert_includes response.fetch(:errors), 'Second line must be empty'
  end

  def test_breaking_changes_lowercase
    message = "chore!: drop support\n\nbreaking change: drop support"
    response = CommitMessageHook.call(message)

    assert_equal false, response.fetch(:success)
    assert_includes response.fetch(:errors), 'Breaking changes footer must be uppercase'
  end

  def test_breaking_changes_title_without_bang
    message = "chore: drop support\n\nBREAKING CHANGE: drop support"
    response = CommitMessageHook.call(message)

    assert_equal false, response.fetch(:success)
    assert_includes response.fetch(:errors), 'Commit tile must append `!` for breaking changes'
  end
end
