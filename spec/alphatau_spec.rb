RSpec.describe Alphatau do
  it 'has a version number' do
    expect(Alphatau::VERSION).not_to be nil
  end

  it 'does something useful' do
    a = Alphatau::Native.instance
    b = Alphatau::Native::Window.new
  end

  it 'returns 6' do
    a = Alphatau::Native.instance
    expect(a.haha 1).to eq 6
  end
end
