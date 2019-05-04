RSpec.describe Alphatau do
  it 'has a version number' do
    expect(Alphatau::VERSION).not_to be nil
  end

  it 'does something useful' do
    a = Alphatau::Native.instance
  end
end
