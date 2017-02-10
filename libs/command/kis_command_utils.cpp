/*
 *  Copyright (c) 2015 Dmitry Kazakov <dimula73@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "kis_command_utils.h"

namespace KisCommandUtils
{
    AggregateCommand::AggregateCommand()
        : m_firstRedo(true) {}

    void AggregateCommand::redo()
    {
        if (m_firstRedo) {
            m_firstRedo = false;

            populateChildCommands();
        }

        m_store.redoAll();
    }

    void AggregateCommand::undo()
    {
        m_store.undoAll();
    }

    void AggregateCommand::addCommand(KUndo2Command *cmd)
    {
        m_store.addCommand(cmd);
    }

    SkipFirstRedoWrapper::SkipFirstRedoWrapper(KUndo2Command *child, KUndo2Command *parent)
        : KUndo2Command(child->text(), parent), m_firstRedo(true), m_child(child) {}

    void SkipFirstRedoWrapper::redo()
    {
        if (m_firstRedo) {
            m_firstRedo = false;
        } else {
            if (m_child) {
                m_child->redo();
            }
            KUndo2Command::redo();
        }
    }

    void SkipFirstRedoWrapper::undo()
    {
        KUndo2Command::undo();
        if (m_child) {
            m_child->undo();
        }
    }

    SkipFirstRedoBase::SkipFirstRedoBase(bool skipFirstRedo, KUndo2Command *parent)
        : KUndo2Command(parent),
          m_firstRedo(skipFirstRedo)
    {
    }

    SkipFirstRedoBase::SkipFirstRedoBase(bool skipFirstRedo, const KUndo2MagicString &text, KUndo2Command *parent)
        : KUndo2Command(text, parent),
          m_firstRedo(skipFirstRedo)
    {
    }

    void SkipFirstRedoBase::redo()
    {
        if (m_firstRedo) {
            m_firstRedo = false;
        } else {
            redoImpl();
            KUndo2Command::redo();
        }
    }

    void SkipFirstRedoBase::undo()
    {
        KUndo2Command::undo();
        undoImpl();
    }

    void SkipFirstRedoBase::setSkipOneRedo(bool value)
    {
        m_firstRedo = true;
    }

    FlipFlopCommand::FlipFlopCommand(bool finalize, KUndo2Command *parent)
        : KUndo2Command(parent),
          m_finalize(finalize),
          m_firstRedo(true)
    {
    }

    void FlipFlopCommand::redo()
    {
        if (!m_finalize) {
            init();
        } else {
            end();
        }

        m_firstRedo = false;
    }

    void FlipFlopCommand::undo()
    {
        if (m_finalize) {
            init();
        } else {
            end();
        }
    }

    void FlipFlopCommand::init() {}
    void FlipFlopCommand::end() {}

    CompositeCommand::CompositeCommand(KUndo2Command *parent)
        : KUndo2Command(parent) {}

    CompositeCommand::~CompositeCommand() {
        qDeleteAll(m_commands);
    }

    void CompositeCommand::addCommand(KUndo2Command *cmd) {
        if (cmd) {
            m_commands << cmd;
        }
    }

    void CompositeCommand::redo() {
        Q_FOREACH (KUndo2Command *cmd, m_commands) {
            cmd->redo();
        }
    }

    void CompositeCommand::undo() {
        Q_FOREACH (KUndo2Command *cmd, m_commands) {
            cmd->undo();
        }
    }
}