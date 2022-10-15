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
    types = COMMIT_TYPES.join('|')

    %r[^(#{types})(\(.+\))?!?: .+]
  end

  def errors
    @errors ||= []
  end
end
