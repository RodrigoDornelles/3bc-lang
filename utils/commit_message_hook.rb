class CommitMessageHook
  COMMIT_TYPES = %w[feat fix chore test ci docs]

  def self.call(message)
    new(message).call
  end

  def call
    return { success: true, errors: [] } if valid_message?

    { success: false, errors: errors }
  end

  private

  attr_reader :message

  def initialize(message)
    @message = message
  end

  def valid_message?
    errors.push('Invalid commit title format') unless title_regex.match?(title) 
    errors.push('Invalid commit title max size (80)')  unless title.size <= 80
    errors.push('Second line must be empty') unless second_line.size == 0

    validate_breaking_changes

    errors.count == 0
  end

  def title
    @title ||= commit_lines.first
  end

  def second_line
    @second_line ||= commit_lines[1] || ''
  end

  def commit_lines
    @commit_lines ||= message.split("\n").filter { |line| !%r[^#].match?(line) }
  end

  def title_regex
    %r[^(#{types})(\(.+\))?!?: .+]
  end

  def validate_breaking_changes
    lowercase_regex = %r[breaking change]
    errors.push('Breaking changes footer must be uppercase') if lowercase_regex.match?(message)

    breaking_changes_format = %r[BREAKING CHANGE: .+]

    return unless breaking_changes_format.match?(message)

    breaking_changes_title_regex = %r[^(#{types})(\(.+\))?!: .+]
    errors.push('Commit tile must append `!` for breaking changes') unless breaking_changes_title_regex.match?(message)
  end

  def types
    COMMIT_TYPES.join('|')
  end

  def errors
    @errors ||= []
  end
end
