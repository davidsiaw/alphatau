RSpec.describe Alphatau do
  it 'has a version number' do
    expect(Alphatau::VERSION).not_to be nil
  end

  it 'does something useful' do
    a = Alphatau::Native.instance
    b = Alphatau::Native::Window.new
  end

  it 'is the correct version' do
    expect(Alphatau::Native.instance.version).to eq 2008
  end
end
