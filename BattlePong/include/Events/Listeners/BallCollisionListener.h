#ifndef BALLCOLLISIONLISTENER_H
#define BALLCOLLISIONLISTENER_H

#include <GameUtilities/Event/Listener.h>

#include <boost/move/utility_core.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;

class BallCollisionListener: public GU::Evt::Listener
{
    public:
        BallCollisionListener();
        void OnEvent(GU::Evt::EventPtr event);
        virtual ~BallCollisionListener();
    protected:
    private:
        src::logger lg;
};

#endif // BALLCOLLISIONLISTENER_H
